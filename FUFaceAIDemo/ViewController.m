//
//  ViewController.m
//  FUFaceAIDemo
//
//  Created by 孙慕 on 2020/8/24.
//  Copyright © 2020 孙慕. All rights reserved.
//

#import "ViewController.h"
#import "FUCamera.h"
#import  <libfuai/fuai_c_api.h>
#import <libfuai/fuai_interface.h>
#import "authpack.h"
#import "FUOpenGLView.h"

@interface ViewController ()<FUCameraDelegate,UITableViewDelegate,UITableViewDataSource>{
    FI_ImageView *imageView;
    FI_FaceProcessor *AImodle;
    const float *landmarks;
    const float *expression;
    int expressionNum;
    
    const float *tougueExpression;
    int tougueExpressionNum;
    
    BOOL useFaceLandmarks;
    BOOL useExpression;
    
}
@property (strong, nonatomic) FUCamera *mCamera ;
@property (strong, nonatomic) FUOpenGLView *renderView;

@property (strong, nonatomic) UISegmentedControl *segmentedControl;

@property (strong, nonatomic) UITableView *mTableView;
@end

@implementation ViewController

-(FUCamera *)mCamera {
    if (!_mCamera) {
        _mCamera = [[FUCamera alloc] init];
        _mCamera.delegate = self ;
    }
    return _mCamera ;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    landmarks = (const float *)malloc(239 * 2);
    expression = (const float *)malloc(46);
    
    FI_Setup(g_auth_package, sizeof(g_auth_package));
    
    NSData *ai_face_processor = [NSData dataWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"ai_face_processor.bundle" ofType:nil]];
    FI_NewFaceProcessorFromBundle([ai_face_processor bytes], (int)ai_face_processor.length, &AImodle);
    
    
//    NSData *tongueData = [NSData dataWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"tongue.bundle" ofType:nil]];
//   FI_NewFaceProcessorFromBundle([ai_face_processor bytes], (int)ai_face_processor.length, &AImodle);
    
    FI_FaceProcessorSetUseFaceLandmark(AImodle, 1);
    FI_FaceProcessorSetUseFaceCapture(AImodle, 1);
    FI_FaceProcessorSetFaceCaptureUseTongueExpression(AImodle, 1);
    
    FI_FaceProcessorSetUseDenseLandmark(AImodle, 1);
    
    [self.mCamera startCapture];
     [_mCamera changeVideoMirrored:NO];
    _renderView = [[FUOpenGLView alloc] initWithFrame:self.view.bounds];
    [self.view addSubview:_renderView];
    
    
//    NSArray *segmentedArray = [[NSArray alloc]initWithObjects:@"75",@"239",nil];
//    _segmentedControl = [[UISegmentedControl alloc]initWithItems:segmentedArray];
//    _segmentedControl.frame = CGRectMake(20.0, 20.0, 250.0, 50.0);
//    _segmentedControl.selectedSegmentIndex = 0;//设置默认选择项索引
//    _segmentedControl.tintColor = [UIColor redColor];
//    [_segmentedControl addTarget:self action:@selector(change:) forControlEvents:UIControlEventValueChanged];
//    [self.view addSubview:_segmentedControl];
    
    [self setupTableView];
    
    [self setupSubView];
    
    useFaceLandmarks = YES;
    useExpression = NO;
    
}

-(void)setupSubView{
    UILabel *faceLabel = [[UILabel alloc] initWithFrame:CGRectMake(20, 40, 100, 40)];
    faceLabel.text = @"人脸关键点:";
    [self.view addSubview:faceLabel];
    
    UISwitch *faceSwitch = [[UISwitch alloc] initWithFrame:CGRectMake(150, 40, 40, 20)];
    [faceSwitch addTarget:self action:@selector(change:) forControlEvents:UIControlEventValueChanged];
    faceSwitch.on = YES;
    [self.view addSubview:faceSwitch];
    
    
    UILabel *eLabel = [[UILabel alloc] initWithFrame:CGRectMake(20, 80, 100, 40)];
    eLabel.text = @"表情检测:";
    [self.view addSubview:eLabel];
    
    UISwitch *eSwitch = [[UISwitch alloc] initWithFrame:CGRectMake(150, 80, 40, 20)];
    [eSwitch addTarget:self action:@selector(eChange:) forControlEvents:UIControlEventValueChanged];
    eSwitch.on = NO;
    [self.view addSubview:eSwitch];
}


-(void)setupTableView{

    _mTableView = [[UITableView alloc]initWithFrame:CGRectMake(self.view.frame.size.width - 110, 0, 110, self.view.frame.size.height) style:UITableViewStylePlain];
    _mTableView.delegate=self;
    _mTableView.dataSource=self;
    _mTableView.backgroundColor=[UIColor clearColor];//设置背景颜色
    _mTableView.userInteractionEnabled=YES;//设置tableView可滑动(默认yes)
    _mTableView.hidden = YES;
    [self.view addSubview:_mTableView];
}


#pragma mark - FUCameraDelegate

-(void)didOutputVideoSampleBuffer:(CMSampleBufferRef)sampleBuffer {
    
    CVPixelBufferRef pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer) ;
    float w = CVPixelBufferGetWidth(pixelBuffer);
    float h = CVPixelBufferGetHeight(pixelBuffer);
    float stride0 = CVPixelBufferGetBytesPerRow(pixelBuffer);
    CVPixelBufferLockBaseAddress(pixelBuffer, 0);
    uint8_t* data = CVPixelBufferGetBaseAddress(pixelBuffer);
    
    
//    FI_FaceProcessorReset(AImodle);
    if (!imageView) {
        FI_NewImageView(&imageView);
        FI_ImageViewInit(imageView, FI_IMAGE_BGRA, w, h,FI_IMAGE_ROTATION_0 , data, stride0, nil, 0, nil, 0);
    }
    FI_ImageViewSetData(imageView, 0, data);
    FI_FaceProcessorProcess(AImodle, imageView);
    
    int facenum = 0;
    int tougue = 0;
    FI_FaceProcessorGetNumResults(AImodle, &facenum);
    
    int count = 0;
    static float ladm[239 * 2] = {0};
    memset(ladm, 0, 239* 2 * sizeof(float));
    
    
    if (facenum > 0 && useFaceLandmarks) {

//        FI_FaceProcessorGetResultAllLandmarks(AImodle, 0, &landmarks, &count);
         FI_FaceProcessorGetResultAllLandmarks(AImodle, 0, &landmarks, &count);

        for (int i = 0; i  < 239 *2; i ++) {
            ladm[i] = landmarks[i];
        }
        
        [self.renderView displayPixelBuffer:pixelBuffer withLandmarks:ladm count:count];
    }else{
        [self.renderView displayPixelBuffer:pixelBuffer];
    }
    
    
    if (useExpression && facenum > 0) {
        FI_FaceProcessorGetResultExpression(AImodle, 0, &expression, &expressionNum);
//        FI_FaceProcessorGetResultTongueExpression(AImodle, tougue, &tougueExpression, &tougueExpressionNum);
        dispatch_async(dispatch_get_main_queue(), ^{
            [_mTableView reloadData];
        });
    }
    

    
    CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);
}

-(void)change:(UISwitch *)seg{
    useFaceLandmarks = seg.on;

}

-(void)eChange:(UISwitch *)seg{
    useExpression = seg.on;
    _mTableView.hidden = !seg.on;
}



//返回行数
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{

    return expressionNum;
}
//返回区数
-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    return 1;
}
//设置行高
-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
    return 30;
}

//设置cell
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{

    static NSString *str=@"indexpath";
    UITableViewCell *cell=[tableView dequeueReusableCellWithIdentifier:str];
    if (!cell) {
        cell=[[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:str];
    }
    //将cell设置为可点击(默认yes)
   // cell.userInteractionEnabled = YES;
    
//    if (indexPath.row < expressionNum) {
        cell.backgroundColor = [UIColor clearColor];
        cell.textLabel.text=[NSString stringWithFormat:@"%ld  %.3lf",indexPath.row,expression[indexPath.row]];
//    }else{
//        cell.backgroundColor = [UIColor clearColor];
//        cell.textLabel.text=[NSString stringWithFormat:@"%ld  %.3lf",indexPath.row,tougueExpression[indexPath.row - expressionNum]];
//    }

//    cell.tintColor = [UIColor blackColor];

    return cell;
}
//点击cell执行该方法
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];//反选

}

@end
