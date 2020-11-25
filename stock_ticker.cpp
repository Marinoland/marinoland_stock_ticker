#include <memory>
#include <map>
#include <sstream>
#include "RestClient.hpp"
#include "ui_framework/MApplication.hpp"

class SymbolEntryGui
{
public:
	typedef std::shared_ptr<SymbolEntryGui> Ref;
	static Ref Create(MGuiFactory* gui, MWindowRef parent)
	{
		Ref ref = std::make_shared<SymbolEntryGui>();
		ref->button = gui->button(*parent, "Add");
		ref->textbox = gui->textBox(*parent);

		ref->button->OnClick([gui, ref]() {

			std::stringstream url;
			url << "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&apikey=KHMO1YK9QKQUFBFQ&symbol="
				<< ref->textbox->GetText();
			web::RestClient().get(url.str().c_str(),
				std::map<std::string, std::string>(),
				[gui, ref](web::RestWebResponse& response) {
					std::stringstream str;
					str << response.getCode();
					gui->messageBox("Quote", str.str().c_str());
					gui->messageBox("json", response.getBody().c_str());
					response.getJson()->asObject(
						[gui](json::JsonObjectNode& root)
						{
							root.get("Global Quote")->asObject(
								[gui](json::JsonObjectNode& quote)
								{
									gui->messageBox("Quote", quote.get("05. price")->to_string().c_str());
								}
							);
						}
					);
				}
			);
		});
		return ref;
	}
	void Reposition(int x, int y, int width, int height)
	{
		textbox->SetPosition(4, y + 4);
		button->SetPosition(width - 44, y + 4);

		textbox->SetDimensions(width - 52, 20);
		button->SetDimensions(40, 20);
	}

private:
	MButtonRef button;
	MTextBoxRef textbox;
};

class MainApp : public MApplication
{
public:
	MainApp() : MApplication ("com.marinoland.testgui") {}
	void Ready(MGuiFactory *gui) {

		mainWindow = gui->window();
		mainWindow->SetTitle("Marinoland Stock Ticker");
		mainWindow->SetDimensions(400, 200);
		mainWindow->Show();

		symbolEntryGui = SymbolEntryGui::Create(gui, mainWindow);
		Reposition();
		MainApp *app = this;
		mainWindow->OnResize([app](int w, int h) { app->Reposition(); });
	}
	void Reposition()
	{
		int width, height;
		mainWindow->GetClientRect(width, height);
		symbolEntryGui->Reposition(4, height - 28, width, 28);
	}
private:
	std::shared_ptr<SymbolEntryGui> symbolEntryGui;
	MWindowRef mainWindow;
};

RUN(MainApp)