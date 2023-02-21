#include <iostream>
#include <pangolin/pangolin.h>

using namespace std;

int main(int argc, char** argv){
    std::cout << "running: " << argv[0] << std::endl;
    
    // 创建名称为“Main”的GUI窗口，尺寸为640×480
    pangolin::CreateWindowAndBind("ANTenna3D",640, 480);
    // 启动深度测试
    glEnable(GL_DEPTH_TEST);

    // Create Camera
    pangolin::OpenGlRenderState s_cam(
        // set Intrinsic parameter
        // 相机分辨率: (w, h) 
        // 焦距:      (fu, fv) 
        // 相机光心:   (u0, v0) 
        // near/far distance: (zNear, zFar)
        pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 100),
        
        // set View Port
        // camera location (x, y, z) 
        // looking at      (lx, ly, lz) 
        // 设置Y轴向上: AxisDirection up
        pangolin::ModelViewLookAt(2, 2, 2, 0, 0, 0, pangolin::AxisZ)
    );

    //  交互视图同控制面板分界
    const int UI_WIDTH = 120;

    // 创建交互视图
    pangolin::Handler3D handler(s_cam);  // 交互相机视图句柄
    // bottom, top: 0 for bottom, 1 for top
    // left, right: 0 for left, 1 for right
    // aspect
    // pangolin::View& d_cam = pangolin::CreateDisplay().SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f/480.0f).SetHandler(&handler);
    pangolin::View& d_cam = pangolin::CreateDisplay().SetBounds(0.0, 1.0, pangolin::Attach::Pix(UI_WIDTH), 1.0, -640.0f/480.0f).SetHandler(&handler);
    
    // 左侧：控制面板
    pangolin::CreatePanel("ui").SetBounds(0.0, 1.0, 0.0, pangolin::Attach::Pix(UI_WIDTH));
    pangolin::Var<bool> A_Button("ui.a_button", false, false);

    while( !pangolin::ShouldQuit() )
    {
        // 清空颜色和深度缓存
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // set background color
        glClearColor (0.1, 0.6, 0.8, 1);

        d_cam.Activate(s_cam);
        
        // cout <<  pangolin::Pushed(A_Button) << endl;

        // 绘制坐标系 Draw Coordinate Line
       	glLineWidth(3);
        glBegin ( GL_LINES );
	    glColor3f ( 0.8f,0.f,0.f );  // R for X-axis
	    glVertex3f( 0.f, 0.f, 0.f );
	    glVertex3f( 1.f, 0.f, 0.f );
	    glColor3f( 0.f, 0.8f,0.f);  // G for Y-axis
	    glVertex3f( 0.f, 0.f, 0.f );
	    glVertex3f( 0.f, 1.f, 0.f );
	    glColor3f( 0.2f,0.2f,1.f);  // B for Z-axis
	    glVertex3f( 0.f, 0.f, 0.f );
	    glVertex3f( 0.f, 0.f, 1.f );
	    glEnd();

        // draw a cube at [0, 0, 0]
        pangolin::glDrawColouredCube();
        
        // draw points
        glPointSize(3.0);
        // 开始画点
        glBegin ( GL_POINTS );
        // 设置点1颜色，rgb值，float类型
        glColor3f(0, 1, 0);
        // 设置点1坐标，3维float类型
        glVertex3f(0, 2, 0);
        // 设置点2颜色、坐标
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 2);
        // 结束画点
        glEnd();
        
        // save image
        // pangolin::SaveWindowOnRender("from_pangolin");

        // 运行帧循环以推进窗口事件
        pangolin::FinishFrame();
    }

    return 0;
}
