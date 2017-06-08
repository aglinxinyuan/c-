#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#define deckSize 52
#define handSize 11
#define s1 hand[0]/13
#define s2 hand[1]/13
#define s3 hand[2]/13
#define s4 hand[3]/13
#define s5 hand[4]/13
#define h1 final[1]==final[0]
#define h2 final[2]==final[1]
#define h3 final[3]==final[2]
#define h4 final[4]==final[3]

using namespace std;

void shuffle(vector<bool> &deck);
void deal(vector<bool> &deck,vector<int> &cards);
void sanitize(string &line); 
void insert(string &line);
void sort(vector<int> &list);
void swap(int &x,int &y);
void openOutputFile(ofstream &out);
bool errorcheck(string line);
bool getoptions(string &inputLine);
int display(vector<int> hand,ofstream &out);
int convert(string x);
int displayFile(string &name);
int dealCard(vector<bool> &deck);
string getName(string title);
string normalize(string line);

int main()
{
	int score,totalScore=0;
	string name,read,again,help;
    vector<bool> deck(deckSize);
    vector<int> hand(handSize);
    srand(time(NULL));
    ofstream out;
    help=getName("First time play this game? (Y/N)");
    if(toupper(help[0])=='Y')
    cout<<"This is a simple card game that you can place an initial bet between one (1) and fifty (50) coins, where each coin is worth $5.00. You will be dealt five (5) cards and allowed to choose which cards, if any, they wish to keep.The computer then determines what amount they have won, if any."<<endl;
    else read=getName("Do you want to read save data? (Y/N)");
    if(toupper(read[0])=='Y')
        totalScore=displayFile(name);
	else
	    name=normalize(getName("Please enter your name"));
	openOutputFile(out);
	out<<name<<endl;
	cout<<"Dear "<<name<<','<<endl;
    do
    {
        deal(deck,hand);
        score=display(hand,out);
        totalScore+=score;
        cout<<"Dear "<<name<<','<<" ur got "<<score<<" coins this game, and ur total score is "<<totalScore<<endl;
        out<<"Dear "<<name<<','<<" ur got "<<score<<" coins this game, and ur total score is "<<endl<<totalScore<<endl;
        again=getName("Do u want to play again? (Y/N)");
    }while(toupper(again[0])=='Y');
    return 0;
}

int display(vector<int> hand,ofstream &out)
{
	int coin,suitValue,face,wild=0;
	string line,swap;
	vector<int> final(6); 
    static string faceValue[13] =
                           {"Ace",
                            "Two",
                            "Three",
                            "Four",
                            "Five",
                            "Six",
                            "Seven",
                            "Eight",
                            "Nine",
                            "Ten",
                            "Jack",
                            "Queen",
                            "King"},
           suit[4] = {"Hearts",
                      "Clubs",
                      "Diamonds",
                      "Spades"};
    
    coin=convert(getName("How many coins you want to bet" ));
    out<<"How many coins you want to bet: "<<coin<<endl
	   <<"The cards in your hand are "<<endl;;
    cout<<"The cards in your hand are "<<endl;
    for(int i=0;i<5;i++)
    {
        suitValue=hand[i]/13;
        face=hand[i]%13;
        cout<<i+1<<'.'<<faceValue[face]<<" of "<<suit[suitValue]<<endl;
        out<<i+1<<'.'<<faceValue[face]<<" of "<<suit[suitValue]<<endl;
        final[i]=face;
        if(face==2)wild++;
    }
    swap==getName("Do u want to swap cards? (Y/N)");
    if(toupper(swap[0])=='Y'&&getoptions(line))
    {
	for(int i=0;i<line.size();i+=2)
         for(char j='1';j<'6';j++)
              if(line[i]==j)
                   hand[j-49]=hand[j-44];
    for(int i=0;i<5;i++)
    {
        suitValue=hand[i]/13;
        face=hand[i]%13;
        cout<<i+1<<'.'<<faceValue[face]<<" of "<<suit[suitValue]<<endl;
        out<<"and you swaped to"<<endl<<i+1<<'.'<<faceValue[face]<<" of "<<suit[suitValue]<<endl;
        final[i]=face;
        if(face==2)wild++
    }
    }
    sort(final);
	    cout<<endl;
	    out<<endl;
    if(wild==0){
	
    if(final[0]==12&&final[1]==11&&final[2]==10&&final[3]==9&&final[4]==0&&s1==s2&&s2==s3&&s3==s4&&s4==s5)
    {
    cout<<"Royal Flush - 2000 coins"<<endl;
    out<<"Royal Flush - 2000 coins"<<endl;
    return coin*1999;
	}
    else if(h1-1&&h2-1&&h3-1&&h4-1&&s1==s2&&s2==s3&&s3==s4&&s4==s5)
    {
    cout<<"Straight Flush - 250 coins"<<endl;
    out<<"Straight Flush - 250 coins"<<endl;
	return coin*249;
    }
    else if((h1&&h2&&h3)||(h2&&h3&&h4))
    {
    cout<<"Four of a Kind - 125 coins"<<endl;
    out<<"Four of a Kind - 125 coins"<<endl;
	return coin*124;
	}
    else if((h1&&h2&&h4)||(h1&&h3&&h4))
    {
    cout<<"Full House - 40 coins"<<endl;
    out<<"Full House - 40 coins"<<endl;
	return coin*39;
    }
    else if(s1==s2&&s2==s3&&s3==s4&&s4==s5)
    {
    cout<<"Flush -  25 points"<<endl;
    out<<"Flush -  25 points"<<endl;
	return coin*24;
    }
    else if((h1-1&&h2-1&&h3-1&&h4-1)||(final[0]==11&&final[1]==10&&final[2]==9&&final[3]==0&&final[4]==12))
    {
    cout<<"Straight - 20 coins"<<endl;
    out<<"Straight - 20 coins"<<endl;
	return coin*19;
    }
    else if((h1&&h2)||(h2&&h3)||(h3&&h4))
    {
    cout<<"Three of a Kind - 15 coins"<<endl;
    out<<"Three of a Kind - 15 coins"<<endl;
	return coin*14;
    }
    else if((h1&&h3)||(h2&&h4)||(h1&&h4))
    {
    cout<<"Two Pair - 10 coins"<<endl;
    out<<"Two Pair - 10 coins"<<endl;
	return coin*9;
    }
    else if((h1&&final[1]>=10)||(h2&&final[2]>=10)||(h3&&final[3]>=10)||(h4&&final[4]>=10))
    {
    cout<<"Pair - 5 coins"<<endl;
    out<<"Pair - 5 coins"<<endl;
	return coin*4;
    }
    else
    return -coin;
}
    else if(wild==1)
    {
    	if(final[0]==12&&final[1]==11&&final[2]==10&&final[3]==9&&s1==s2&&s2==s3&&s3==s4)
    {
    cout<<"Royal Flush - 2000 coins"<<endl;
    out<<"Royal Flush - 2000 coins"<<endl;
    return coin*1999;
	}
    else if(h1-1&&h2-1&&h3-1&&s1==s2&&s2==s3&&s3==s4)
    {
    cout<<"Straight Flush - 250 coins"<<endl;
    out<<"Straight Flush - 250 coins"<<endl;
	return coin*249;
    }
    else if((h1&&h2)||(h2&&h3))
    {
    cout<<"Four of a Kind - 125 coins"<<endl;
    out<<"Four of a Kind - 125 coins"<<endl;
	return coin*124;
	}
    else if((h1&&h2)||(h1&&h3))
    {
    cout<<"Full House - 40 coins"<<endl;
    out<<"Full House - 40 coins"<<endl;
	return coin*39;
    }
    else if(s1==s2&&s2==s3&&s3==s4)
    {
    cout<<"Flush -  25 points"<<endl;
    out<<"Flush -  25 points"<<endl;
	return coin*24;
    }
    else if((h1-1&&h2-1&&h3-1)||(final[0]==11&&final[1]==10&&final[2]==9&&final[3]==0))
    {
    cout<<"Straight - 20 coins"<<endl;
    out<<"Straight - 20 coins"<<endl;
	return coin*19;
    }
    else if((h1)||(h2)||(h3))
    {
    cout<<"Three of a Kind - 15 coins"<<endl;
    out<<"Three of a Kind - 15 coins"<<endl;
	return coin*14;
    }
    else if((h1)||(h2)||(h1))
    {
    cout<<"Two Pair - 10 coins"<<endl;
    out<<"Two Pair - 10 coins"<<endl;
	return coin*9;
    }
    else
    {
    cout<<"Pair - 5 coins"<<endl;
    out<<"Pair - 5 coins"<<endl;
	return coin*4;
	}} 
    else if(wild==2)
    {
    	if(final[0]==12&&final[1]==11&&final[2]==10&&s1==s2&&s2==s3)
    {
    cout<<"Royal Flush - 2000 coins"<<endl;
    out<<"Royal Flush - 2000 coins"<<endl;
    return coin*1999;
	}
    else if(h1-1&&h2-1&&s1==s2&&s2==s3)
    {
    cout<<"Straight Flush - 250 coins"<<endl;
    out<<"Straight Flush - 250 coins"<<endl;
	return coin*249;
    }
    else if((h1)||(h2))
    {
    cout<<"Four of a Kind - 125 coins"<<endl;
    out<<"Four of a Kind - 125 coins"<<endl;
	return coin*124;
    }
    
	}
    else if(wild==3)
    {
    	if(final[0]==12&&final[1]==11&&s1==s2)
    {
    cout<<"Royal Flush - 2000 coins"<<endl;
    out<<"Royal Flush - 2000 coins"<<endl;
    return coin*1999;
	}
    else if(h1-1&&s1==s2)
    {
    cout<<"Straight Flush - 250 coins"<<endl;
    out<<"Straight Flush - 250 coins"<<endl;
	return coin*249;
    }
    else
	return coin*124;
    }
    else if(wild==4)
	   return coin*1999;
}

int displayFile(string &name)
{
    bool again;
    string fileName,data;
    ifstream in;
    do
    {
        again=false;
        fileName=getName("Please enter the name of save data");
        cout<<"Attempting to open "<<fileName<<endl;
        in.open(fileName.c_str());
        if(in.fail())
        {
            cout<<"That file does not exist. Please re-enter"<<endl;
            in.close();
            in.clear();
            again=true;
        }
    }while(again);
    getline(in,name);
    while(getline(in,data))
        cout<<data<<endl;
    in.close(); 
    return convert(data);
}

string getName(string title)
{
    string name;
    do
    {
        cout<<title<<": ";
        getline(cin,name);
    }while(name.empty());
    return name;
}


void openOutputFile(ofstream &out)
{
    ifstream in;
    string fileName,answer;
    bool again;
    do
    {
        again = false;
        fileName=getName("What is the name of the file you wish to save game data? ");
        in.open(fileName.c_str());
        if(in.fail())
        {
            in.close();
            out.open(fileName.c_str());
        }
        else
        {
            in.close();
            answer=getName("Do you want to (R)e-enter, (A)ppend, (O)verwrite, or (Q)uit? ");
            switch(toupper(answer[0]))
            {
 
                case 'A' : out.open(fileName.c_str(), ios::app);
                           break;
                case 'O' : out.open(fileName.c_str());
                           break;
                case 'Q' : exit(1);
                default  : cout<<"I did not understand your entry. Please re-enter the file name"<<endl;
                case 'R' : again = true;
 
            }
         }
    }while(again);
 
}

void shuffle(vector<bool> &deck)
{
    for(int i=0;i<deckSize;i++)
        deck[i]=false;
}

int dealCard(vector<bool> &deck)
{
    int card;
    while(deck[card=rand()%deckSize]);
    deck[card]=true;
    return card;
}

void deal(vector<bool> &deck,vector<int> &hand)
{
    static int taken=0;
    if(taken>35)
    {
        shuffle(deck);
        taken=0;
    }
    for(int i=0;i<handSize;i++)
        hand[i]=dealCard(deck);
    taken+=handSize;
}

bool getoptions(string &inputLine)
{
bool repeat;
do
{
repeat=false;
inputLine=getName("Please enter numbers of cards you wish to swap");
if(inputLine.empty())
cout<<inputLine.empty()<<endl;
return false;
sanitize(inputLine);
insert(inputLine);
repeat=errorcheck(inputLine);
}while(repeat);
return true;
}

bool errorcheck(string line)
{
int sum;
for(int i=0;i<line.size();i+=2)
{
sum=0;
for(int j='1';j<'6';j++)
if(line[i]==j)
sum++;
if(sum==0)
{
cout<<"Please read the directions, and try again!"<<endl<<endl;
return true;
}
}
return false;
}

void sanitize(string &line)
{
int pos=-1;
while(line[0]==' ')
line.erase(0,1);
while((pos=line.find(' ',pos+1))<line.size())
while(line[pos+1]==' ')
line.erase(pos+1,1);
while(line[line.size()]==' ')
line.erase(line.size()-1,line.size());
}

void insert(string &line)
{
int pos;
do
{
pos=line.find(' ');
line[pos]=',';
}while(pos<line.size());
}

void sort(vector<int> &list)
{
for(int i = 0; i < list.size(); i++)
for(int j = 0; j < list.size(); j++)
if(list[i]>list[j])
swap(list[i], list[j]);
}

void swap(int &x, int &y)
{
int temp = x;
x = y;
y = temp;
}

int convert(string x)
{
    int ans;
    stringstream ben;
    ben<<x;
    ben>>ans;
    return ans;
}

string normalize(string line)
{
    line[0]=toupper(line[0]);
    for(int i=1;i<line.size();i++)
        line[i]=tolower(line[i]);
    return line;
}
