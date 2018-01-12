class thData
{

public:
  int idThread; //id-ul thread-ului tinut in evidenta de acest program
  int cl;       //descriptorul intors de accept
  char username[20];
public:
  thData(int idThread, int cl, char username[20]);
  thData(thData *ptr);
  void setUsername(char username[20]);
};