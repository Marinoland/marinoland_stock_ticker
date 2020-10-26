#include "ui_framework/MApplication.hpp"

class MainApp : public MApplication {
public:
	MainApp() : MApplication ("com.marinoland.testgui") {}
	void Ready(MGuiFactory *gui) {

		mainWindow = gui->window();
		//buttonBox = gui->buttonBox(*mainWindow);
		exitButton = gui->button(*mainWindow, "Clicky");

		mainWindow->SetTitle("Super Window");
		mainWindow->SetDimensions(400, 200);
		mainWindow->Show();
		exitButton->OnClick([&] () { mainWindow->Close(); });
	}
private:
	MWindowRef mainWindow;
	//MButtonBoxRef buttonBox;
	MButtonRef exitButton;
};

RUN(MainApp)