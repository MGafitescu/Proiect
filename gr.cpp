#include <TGUI/TGUI.hpp>
int logged=0;

void login(tgui::EditBox::Ptr username)
{
    std::cout << "Username: " << username->getText().toAnsiString() << std::endl;
    logged=1;
}

void login1()
{
    printf("Apasat");
logged=2;
}
void loadWidgets( tgui::Gui& gui )
{
    // Load the black theme
    auto theme = tgui::Theme::create("widgets/Black.txt");

    // Get a bound version of the window size
    // Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
    auto windowWidth = tgui::bindWidth(gui);
    auto windowHeight = tgui::bindHeight(gui);

    // Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
    auto picture = tgui::Picture::create("bg.jpg");
    picture->setSize(tgui::bindMax(800, windowWidth), tgui::bindMax(600, windowHeight));
    gui.add(picture);

     tgui::Label::Ptr msg = theme->load("Label");
    msg->setSize(windowWidth *2/3, windowHeight / 4);
    msg->setPosition(windowWidth / 6, windowHeight /10);
    msg->setTextSize(92);
    msg->setFont("fonts/DejaVuSans.ttf");
    msg->setText("QuizzGame");
    gui.add(msg);

    // Create the username edit box
    tgui::EditBox::Ptr editBoxUsername = theme->load("EditBox");
    editBoxUsername->setSize(windowWidth * 2/3, windowHeight / 8);
    editBoxUsername->setPosition(windowWidth / 6, windowHeight / 2);
    editBoxUsername->setDefaultText("Username");
    gui.add(editBoxUsername, "Username");


    // Create the login button
    tgui::Button::Ptr button = theme->load("Button");
    button->setSize(windowWidth / 2, windowHeight / 6);
    button->setPosition(windowWidth / 4, windowHeight * 7/10);
    button->setText("Login");
    gui.add(button);

    // Call the login function when the button is pressed
    button->connect("pressed", login, editBoxUsername);
}


void loadWidgets2( tgui::Gui& gui, char* intrebare, char* a, char* b, char* c , char* d)
{
    // Load the black theme
    auto theme = tgui::Theme::create("widgets/Black.txt");

    // Get a bound version of the window size
    // Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
    auto windowWidth = tgui::bindWidth(gui);
    auto windowHeight = tgui::bindHeight(gui);

    // Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
    auto picture = tgui::Picture::create("bg.jpg");
    picture->setSize(tgui::bindMax(800, windowWidth), tgui::bindMax(600, windowHeight));
    gui.add(picture);

 
     
    tgui::TextBox::Ptr msg = theme->load("TextBox");
    msg->setSize(windowWidth / 1.5, windowHeight / 5);
    msg->setPosition(windowWidth / 6, windowHeight /10);
    msg->setText(intrebare);
    gui.add(msg);



    // Create the login button
    tgui::Button::Ptr button1 = theme->load("Button");
    button1->setSize(windowWidth / 2.5, windowHeight / 6);
    button1->setPosition(windowWidth / 20, windowHeight /2.2);
    button1->setText(a);
    gui.add(button1);

      tgui::Button::Ptr button2 = theme->load("Button");
    button2->setSize(windowWidth / 2.5, windowHeight / 6);
    button2->setPosition(windowWidth /20*11, windowHeight /2.2);
    button2->setText(b);
    gui.add(button2);

      tgui::Button::Ptr button3 = theme->load("Button");
    button3->setSize(windowWidth / 2.5, windowHeight / 6);
    button3->setPosition(windowWidth /20, windowHeight /1.4);
    button3->setText(c);
    gui.add(button3);

      tgui::Button::Ptr button4 = theme->load("Button");
    button4->setSize(windowWidth / 2.5, windowHeight / 6);
    button4->setPosition(windowWidth / 20*11, windowHeight /1.4);
    button4->setText(d);
    gui.add(button4);

    // Call the login function when the button is pressed
    button1->connect("pressed", login1);
    button2->connect("pressed", login1);
    button3->connect("pressed", login1);
    button4->connect("pressed", login1);
}

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "QuizzGame");
    tgui::Gui gui(window);

    try
    {
        // Load the widgets
        loadWidgets(gui);
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        return 1;
    }

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // When the window is closed, the application ends
            if (event.type == sf::Event::Closed)
                window.close();

            // When the window is resized, the view is changed
            else if (event.type == sf::Event::Resized)
            {
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                gui.setView(window.getView());
            }

            char intrebare[100]="Intrebare1";
        char a[100]="A";
        char b[100]="B";
        char c[100]="C";
        char d[100]="D";
        if(logged==1)
        loadWidgets2(gui,intrebare,a,b,c,d);
        strcpy(intrebare,"Intrebare 2");
        if(logged==2)
      loadWidgets2(gui,intrebare,a,b,c,d);
            // Pass the event to all the widgets
            gui.handleEvent(event);
        }

        window.clear();
        
        // Draw all created widgets
        gui.draw();

        window.display();
    }

    return EXIT_SUCCESS;
}