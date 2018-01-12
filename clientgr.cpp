/* cliTCPIt.c - Exemplu de client TCP
   Trimite un numar la server; primeste de la server numarul incrementat.
         
   Autor: Lenuta Alboaie  <adria@infoiasi.ro> (c)2009
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <TGUI/TGUI.hpp>

/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port;
int screen = 0;
int question = 0;
char user[1000];
char answer;
int logged=0;

void showQuestion(char question[1000], int nr)
{

    for (int i = 0; i < nr; i++)
    {
        if (question[i] == '~')
            printf("\n");
        else
            printf("%c", question[i]);
    }
    printf("\n");
}

void login(tgui::EditBox::Ptr username)
{
    const char *car=username->getText().toAnsiString().c_str();
    strcpy(user,car);
    logged=1;
    question++;
    screen = question;
}

void login1(char c)
{
    answer = c;
    question++;
    screen = question;
}
void loadWidgets(tgui::Gui &gui)
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
    msg->setSize(windowWidth * 2 / 3, windowHeight / 4);
    msg->setPosition(windowWidth / 6, windowHeight / 10);
    msg->setTextSize(92);
    msg->setFont("fonts/DejaVuSans.ttf");
    msg->setText("QuizzGame");
    gui.add(msg);

    // Create the username edit box
    tgui::EditBox::Ptr editBoxUsername = theme->load("EditBox");
    editBoxUsername->setSize(windowWidth * 2 / 3, windowHeight / 8);
    editBoxUsername->setPosition(windowWidth / 6, windowHeight / 2);
    editBoxUsername->setDefaultText("Username");
    gui.add(editBoxUsername, "Username");

    // Create the login button
    tgui::Button::Ptr button = theme->load("Button");
    button->setSize(windowWidth / 2, windowHeight / 6);
    button->setPosition(windowWidth / 4, windowHeight * 7 / 10);
    button->setText("Login");
    gui.add(button);

    // Call the login function when the button is pressed
    button->connect("pressed", login, editBoxUsername);
}

void loadWidgets2(tgui::Gui &gui, char *intrebare, char *a, char *b, char *c, char *d)
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
    msg->setPosition(windowWidth / 6, windowHeight / 10);
    msg->setText(intrebare);
    gui.add(msg);

    // Create the login button
    tgui::Button::Ptr button1 = theme->load("Button");
    button1->setSize(windowWidth / 2.5, windowHeight / 6);
    button1->setPosition(windowWidth / 20, windowHeight / 2.2);
    button1->setText(a);
    gui.add(button1);

    tgui::Button::Ptr button2 = theme->load("Button");
    button2->setSize(windowWidth / 2.5, windowHeight / 6);
    button2->setPosition(windowWidth / 20 * 11, windowHeight / 2.2);
    button2->setText(b);
    gui.add(button2);

    tgui::Button::Ptr button3 = theme->load("Button");
    button3->setSize(windowWidth / 2.5, windowHeight / 6);
    button3->setPosition(windowWidth / 20, windowHeight / 1.4);
    button3->setText(c);
    gui.add(button3);

    tgui::Button::Ptr button4 = theme->load("Button");
    button4->setSize(windowWidth / 2.5, windowHeight / 6);
    button4->setPosition(windowWidth / 20 * 11, windowHeight / 1.4);
    button4->setText(d);
    gui.add(button4);

    // Call the login function when the button is pressed
    button1->connect("pressed", login1, 'A');
    button2->connect("pressed", login1, 'B');
    button3->connect("pressed", login1, 'C');
    button4->connect("pressed", login1, 'D');
}

int main(int argc, char *argv[])
{
    int sd;                    // descriptorul de socket
    struct sockaddr_in server; // structura folosita pentru conectare
                               // mesajul trimis

    /* exista toate argumentele in linia de comanda? */
    if (argc != 3)
    {
        printf("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
        return -1;
    }

    /* stabilim portul */
    port = atoi(argv[2]);

    /* cream socketul */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Eroare la socket().\n");
        return errno;
    }

    /* umplem structura folosita pentru realizarea conexiunii cu serverul */
    /* familia socket-ului */
    server.sin_family = AF_INET;
    /* adresa IP a serverului */
    server.sin_addr.s_addr = inet_addr(argv[1]);
    /* portul de conectare */
    server.sin_port = htons(port);

    /* ne conectam la server */
    if (connect(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
        perror("[client]Eroare la connect().\n");
        return errno;
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "QuizzGame");
    tgui::Gui gui(window);

    char intrebare[100] = "Intrebare1";
    char a[100] = "A1";
    char b[100] = "B1";
    char c[100] = "C1";
    char d[100] = "D1";
    try
    {
        // Load the widgets
        loadWidgets(gui);
    }
    catch (const tgui::Exception &e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        return 1;
    }
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(0);
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

            while(logged==0);
            if (write(sd, user, 20) <= 0)
            {
                perror("[client]Eroare la write() spre server.\n");
                return errno;
            }
            int nr, index, punctaj;
            char enter;
            if (read(sd, &index, sizeof(int)) < 0)
            {
                perror("[client]Eroare la read() de la server.\n");
                return errno;
            }
            for (int i = 1; i <= index; i++)
            {

                char question[1000];
                if (read(sd, &nr, sizeof(int)) < 0)
                {
                    perror("[client]Eroare la read() de la server.\n");
                    return errno;
                }
                if (read(sd, question, nr) < 0)
                {
                    perror("[client]Eroare la read() de la server.\n");
                    return errno;
                }

                showQuestion(question, nr);
                if (screen == i)
                {
                    gui.removeAllWidgets();
                    loadWidgets2(gui, intrebare, a, b, c, d);
                    screen = 0;
                }
                /* citirea mesajului */

                read(0, &answer, sizeof(char));
                read(0, &enter, sizeof(char));

                /* trimiterea mesajului la server */
                if (write(sd, &answer, sizeof(char)) <= 0)
                {
                    perror("[client]Eroare la write() spre server.\n");
                    return errno;
                }
                char right;
                if (read(sd, &right, sizeof(char)) < 0)
                {
                    perror("[client]Eroare la read() de la server.\n");
                    return errno;
                }
                if (right == 'Y')
                    printf("Raspunsul este corect.\n\n");
                else
                    printf("Raspunsul este gresit.\n\n");
            }

            if (read(sd, &punctaj, sizeof(int)) < 0)
            {
                perror("[client]Eroare la read() de la server.\n");
                return errno;
            }
            printf("Jocul este gata.%s, ai obtinut %d din %d puncte.Bravo!\n", user, punctaj, index);
            /* inchidem conexiunea, am terminat */
            // Pass the event to all the widgets
            gui.handleEvent(event);
        }

        window.clear();

        // Draw all created widgets
        gui.draw();

        window.display();
    }

    close(sd);
}
