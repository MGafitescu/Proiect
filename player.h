class Player
{
private:  
  int id;
  char username[20];
  int punctaj;
public:
  Player(int id, char username[20]);
  char * getUsername();
  void setPunctaj(int punctaj);
  int getPunctaj();
};