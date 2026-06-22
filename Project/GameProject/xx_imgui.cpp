//必須（imguiフォルダのソースファイルすべて）
//https://github.com/ocornut/imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_ja_gryph_ranges.h"

//--------------------------------------------
//グローバル変数領域
//-------------------------------------------

CVector4D color(0,0,0,1);
CImage img;
void MainLoop(void) {
	//--------------------------------------------------------------
	//ゲーム中の動きはここに書く
	//ゲーム中はこの関数_を1秒間に60回呼び出している
	//--------------------------------------------------------------

	//必須--------------------------------------------------------------------
	//GUIの描画の前に一度だけ呼び出す
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//Push→Pop
	//背景色の再設定
	ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.0f, 0.0f, 0.1f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(color.x, color.y, color.z, color.w));
	//ここから一つのウインドウ描画開始
	ImGui::Begin(u8"Option", nullptr);
	//スライダー表示
	ImGui::SliderFloat(u8"Red", &color.x, 0.0f, 1.0f);
	//テキスト表示(printfと同じ書式)
	ImGui::Text(u8"%-20s %05d",u8"テキスト",123); ImGui::SameLine();
	//画像ボタン(事前にimg.Drawを一度だけ実行し、テクスチャーをVRAMへ配置しておく)
	if (ImGui::ImageButton((ImTextureID)img.mp_texture->m_bufID, ImVec2(64, 64))) {
		//ボタンが押された時の処理
		printf("push");
	}
	//ここまで
	ImGui::End();

	//ウインドウサイズ指定
	ImGui::SetNextWindowSize(ImVec2(200,100));
	ImGui::Begin(u8"Exit", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	
	if (ImGui::Button(u8"ExitGame"))
		glfwSetWindowShouldClose(GL::window, GL_TRUE);
	ImGui::End();

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	//必須--------------------------------------------------------------------
	// Rendering
	//１更新で一回の呼び出し
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	//---------------------------------------------------------------------------




	

}

void Init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);//ブレンドの有効化
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//固定シェーダー用
	glDisable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_ALPHA_TEST);
	//★フレームレート設定
	CFPS::SetFPS(DEFAULT_FPS);
	//垂直同期OFF
	glfwSwapInterval(0);
	//フレーム制御初期化
	CFPS::Init();
	//ボタンの設定
	CInput::Init();
	CInput::SetButton(0, CInput::eButton1, 'Z');
	CInput::SetButton(0, CInput::eButton2, 'X');
	CInput::SetButton(0, CInput::eButton3, 'C');
	CInput::SetButton(0, CInput::eButton4, VK_LSHIFT);
	CInput::SetButton(0, CInput::eButton5, VK_SPACE);
	CInput::SetButton(0, CInput::eButton10, VK_RETURN);
	CInput::SetButton(0, CInput::eUp, 'W');
	CInput::SetButton(0, CInput::eDown, 'S');
	CInput::SetButton(0, CInput::eLeft, 'A');
	CInput::SetButton(0, CInput::eRight, 'D');
	CInput::SetButton(0, CInput::eMouseL, VK_LBUTTON);
	CInput::SetButton(0, CInput::eMouseR, VK_RBUTTON);
	CInput::SetButton(0, CInput::eMouseC, VK_MBUTTON);

	//★マウス非表示
//	CInput::ShowCursor(false);
//	CInput::SetMouseInside(true);
	CInput::Update();
	CInput::Update();


	//ライト設定
	CLight::SetType(0, CLight::eLight_Direction);
	CLight::SetPos(0, CVector3D(0, 200, 200));
	CLight::SetDir(0, CVector3D(0, -1, 0.5).GetNormalize());
	CLight::SetColor(0, CVector3D(0.4f, 0.4f, 0.4f), CVector3D(0.6f, 0.6f, 0.6f));



	CLight::SetFogParam(CVector4D(1, 1, 1, 1), 1200, 1400);

	//カメラ初期化
	CCamera::GetCamera()->LookAt(CVector3D(5, 5, 5),
		CVector3D(0, 0, 0),
		CVector3D(0.0, 1.0, 0.0));

	SetCurrentDirectory("data");


	//★ポストエフェクトを生成		画面解像度,被写界深度オフセット
	//CRendaring::CreatInstance(SCREEN_WIDTH, SCREEN_HEIGHT,CVector3D(0.1f,0.85f,0.5f), CRendaring::RendringType::eForward);
	//CRendaring::GetInstance()->SetEdge(false);
	//CRendaring::GetInstance()->SetDOF(false);
	//CRendaring::GetInstance()->SetGlare(true,60.0f,2.0f);

	CShader::GetInstance("StaticMesh");
	CShader::GetInstance("SkinMesh");
	CSound::GetInstance();
	CLight::Init();


	//-----------------------------------------------------
	//初期化の命令を書く
	//ゲーム起動時に一度だけ呼ばれる
	//-----------------------------------------------------

	
	//imgui必須--------------------------------------------------------------------
// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	//日本語入力用フォント指定
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 32.0f, NULL, glyphRangesJapanese);
	//(void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

	ImGui_ImplGlfw_InitForOpenGL(GL::window, true);
	ImGui_ImplOpenGL2_Init();

	// Setup style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	//-------------------------------------------------------------------------

	ADD_RESOURCE("Image", CImage::CreateImage("UI/circle_green.png"));
	img = COPY_RESOURCE("Image", CImage);
	//一度Drawを実行しテクスチャーをVRAMへ転送しておく
	img.Draw();

}


void Release()
{
	//Base::ClearInstance();
	CMultiThread::ClearInstance();
	CSound::ClearInstance();
	CResourceManager::ClearInstance();
}

static void ResizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);

	//画面解像度変動
	CCamera::GetCamera()->SetSize((float)w, (float)h);
	//画面解像度固定
	//CCamera::GetCamera()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera::GetCamera()->Viewport(0, 0, (float)w, (float)h);
	CCamera::GetCurrent()->Perspective(DtoR(60.0), (float)w / (float)h, 0.5, 1000.0);

	glfwGetWindowPos(window, &GL::window_x, &GL::window_y);
	GL::UpdateWindowRect(GL::window_x, GL::window_y, w, h);
	CInput::UpdateClipCursor(true);

}
static void WheelCallback(GLFWwindow* _window, double _offsetx, double _offsety) {
	CInput::AddMouseWheel((int)_offsety);

}
static void PosCallback(GLFWwindow* _window, int x, int y) {
	GL::window_x = x;
	GL::window_y = y;
	GL::UpdateWindosRect(x, y, GL::window_width, GL::window_height);
	CInput::UpdateClipCursor(true);

}
static void FocusCallback(GLFWwindow* _window, int f) {
	CInput::UpdateClipCursor(f);
	GL::focus = f;
}

static void error_callback(int error, const char* description)
{
	printf("Error: %s\n", description);
}

//フルスクリーン?ウインドウモードの切り替え
//Alt+Enterで切り替える
void CheckFullScreen() {
	static int key_enter = 0;
	int key_enter_buf = key_enter;
	if (key_enter_buf ^ (key_enter = glfwGetKey(GL::window, GLFW_KEY_ENTER)) && key_enter && (glfwGetKey(GL::window, GLFW_KEY_LEFT_ALT) || glfwGetKey(GL::window, GLFW_KEY_RIGHT_ALT))) {
		GL::ChangeFullScreen(!GL::full_screen);
	}
}

int __main(int* argcp, char** argv) {
	// メモリリーク検出
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//★.dllのパス指定
	char path[256];
	GetCurrentDirectory(256, path);
	strcat_s(path, 255, "\\dll");
	SetDllDirectory(path);

	//OpenGL4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) return -1;
	//	glutInit(argcp, argv);

	GL::window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple", nullptr, nullptr);
	glfwGetWindowSize(GL::window, &GL::window_width, &GL::window_height);
	glfwGetWindowPos(GL::window, &GL::window_x, &GL::window_y);

	glfwSetFramebufferSizeCallback(GL::window, ResizeCallback);
	glfwSetScrollCallback(GL::window, WheelCallback);
	glfwSetWindowFocusCallback(GL::window, FocusCallback);
	glfwSetWindowPosCallback(GL::window, PosCallback);
	if (!GL::window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(GL::window);
	ResizeCallback(GL::window, SCREEN_WIDTH, SCREEN_HEIGHT);

	GLenum err = glewInit();
	if (err == GLEW_OK) {
		printf("%s\n", glewGetString(GLEW_VERSION));
	}
	else {
		printf("%s\n", glewGetErrorString(err));
		getchar();
		return -1;
	}
	HDC glDc = wglGetCurrentDC();
	GL::hWnd = WindowFromDC(glDc);
	
	//★前面ボーダー無し
	//SetWindowLong(GL::hWnd, GWL_STYLE, WS_MAXIMIZE);
	//SetWindowPos(GL::hWnd, HWND_TOP, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_SHOWWINDOW);
	Init();


	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	LARGE_INTEGER time_buf;
	QueryPerformanceCounter(&time_buf);
	float fps = 0;
	while (!glfwWindowShouldClose(GL::window)) {
		CheckFullScreen();
		CInput::Update();
		//各バッファーをクリア
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		MainLoop();
		FONT_T()->Draw(0, 32, 1, 0, 0, "fps:%3d", (int)CFPS::GetFPS(), (int)fps);



		glfwSwapBuffers(GL::window);
		CFPS::Wait();

		glfwPollEvents();
		if (glfwGetKey(GL::window, GLFW_KEY_ESCAPE)) {
			GL::isQuit = true;
			glfwSetWindowShouldClose(GL::window, GL_TRUE);
		}

	}

	glfwTerminate();

	Release();
	return 0;
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR argv, INT argc)
{
	return __main(&__argc, __argv);
}

int main(int argc, char** argv)
{
	return __main(&argc, argv);
}
