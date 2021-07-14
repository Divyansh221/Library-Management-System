/*
19CS10027
Divyansh Bhatia
LIBRARY MANAGEMENT SYSTEM
*/

#include<bits/stdc++.h>
#include <dirent.h>         // Format of directory entries
using namespace std;

class Paragraphs{       // Class paragraphs to store paragraphs and its related information
    public:
        string paragraph;
        map<string, int> frequency;         // To store frequency of each unique word in a paragraph
        int paragraphStartLineNumber;       // To store paragraph starting line number
        int paragraphEndLineNumber;         // To store paragraph ending line number
        void identify(string myObj){
            char ch;
            string temp = myObj;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);       // Case-insensitive
            string word = "";
            for(int i = 0; i < temp.length(); i++){
                ch = temp[i];
                if(ch >= 'a' && ch <= 'z'){
                    word.push_back(ch);
                }
                else{
                    frequency[word]++;
                    word = "";
                }
            }
        }
};

class Novel{        // All functionalities related to Novels
    private:
        map<int, vector<Paragraphs> > chapter;          // To store all chapters and paragraphs in it with its chapter number
    public:
        struct sort_pred {
            bool operator()(const std::pair<int, pair<int, Paragraphs> > &left, const std::pair<int, pair<int, Paragraphs> > &right) {
                return left.first < right.first;
            }       // So that we can sort solely based on second item of vector of pairs
        };
        void findMaxFrequency(string fileName, string command){         // Given an input word, the LMS should be able to
                                                                        // show the top 5 chapters, or top 5 paragraphs, where this word appears most of the times.
            ifstream MyReadFile((command + fileName).c_str());
            string myText;
            int indexNumber = 0, lineNumber = 1;
            string check;
            while(getline (MyReadFile, myText)){
                if(myText.length() >= 7) check = myText.substr(0, 7);
                if(check == "CHAPTER"){
                    lineNumber++;       // Line number ftarting from line 1
                    indexNumber++;      // Chapter number count
                    bool flag = true;
                    while(getline (MyReadFile, myText)){
                        lineNumber++;
                        if(flag == false){
                            lineNumber++;
                            if(myText == "") break;         // End of a chapter
                        }
                        string x = "";
                        x += myText;
                        x += ' ';
                        flag = true;
                        Paragraphs myObj;
                        myObj.paragraphStartLineNumber = lineNumber - 1; 
                        while(getline (MyReadFile, myText)){
                            if(myText.length() == 0){
                                lineNumber--;
                                flag = false;
                                break;
                            }
                            x += myText;
                            x += ' ';
                            lineNumber++;
                        }
                        myObj.paragraph = x;
                        myObj.paragraphEndLineNumber = lineNumber;
                        myObj.identify(x);
                        chapter[indexNumber].push_back(myObj);      // Add this paragraph to chapter[indexNumber]
                        lineNumber++;
                    }
                }
                else lineNumber++;
            }
            cout<<"Enter the word, you want to find max occurance of :  ";
            string word;
            cin>>word;
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            int index = 1;
            vector<pair<int, int> > CHAPTER;
            vector<pair<int, pair<int, Paragraphs> > > PARAGRAPH;
            for(auto i : chapter){
                int count = 0;
                for(auto j : i.second){
                    count += j.frequency[word];
                    PARAGRAPH.push_back({j.frequency[word], {index, j}});
                }
                CHAPTER.push_back({count, index});
                index++;
            }
            sort(CHAPTER.begin(), CHAPTER.end());
            sort(PARAGRAPH.begin(), PARAGRAPH.end(), sort_pred());
            cout<<"What do you want to get : top 5 chapters (A) or top 5 paragraphs (B) : ";
            char myChoice;
            cin>>myChoice;
            int count = 0;
            if(myChoice == 'A'){
                cout<<"Top 5 chapters are : "<<endl;        //  Top 5 chapters
                for (int i = CHAPTER.size() - 1; i >= CHAPTER.size() - 5; i--){
                    if(CHAPTER[i].first == 0) continue;
                    cout<<"CHAPTER - "<<CHAPTER[i].second<<"  :  "<<CHAPTER[i].first<<endl;
                    count++;
                }
            }
            else{
                cout<<"Top 5 paragraphs are : "<<endl;      // Top 5 paragraphs 
                for (int i = PARAGRAPH.size() - 1; i >= PARAGRAPH.size() - 5; i--){
                    if(PARAGRAPH[i].first == 0) continue;
                    Paragraphs myObj = PARAGRAPH[i].second.second;
                    cout<<"Chapter - "<<PARAGRAPH[i].second.first<<endl;
                    cout<<"Frequency count : "<<PARAGRAPH[i].first<<endl;
                    cout<<"Start line : "<<myObj.paragraphStartLineNumber<<endl;
                    cout<<"End line : "<<myObj.paragraphEndLineNumber<<endl;
                    cout<<myObj.paragraph;
                    cout<<endl;
                    count++;
                }
            }
            if(count == 0){
                cout<<"No occurance of the word!"<<endl;        // If the input word doesn't exists
            }
        }
};

class Play{         // All functionalities related to plays
    private:
        vector<map<string, int> > scene;        // To store all character name SCENE wise, i.e. for all scenes
    public:
        bool isUpper(const string& s) {
            return all_of(s.begin(), s.end(), [](unsigned char c){
                if(c == ' ') return 1;          // Conditioner to allow spaces in std isUpper fucntion 
                return isupper(c); 
            });
        }
        void findAllCharacters(string fileName, string command){        //  Utility function to find all character that are present in atleast one scene with user input character
            ifstream MyReadFile((command + fileName).c_str());
            string myText;
            int indexNumber = 0;  
            string check;
            map<string, int> mp;
            int lineNumber = 1;         // To keep track of line number
            while(getline (MyReadFile, myText)){
                if(myText.length() >= 5) check = myText.substr(0, 5);
                if(check == "SCENE"){
                    check = "";
                    scene.push_back(mp);
                    mp.clear();     // Add to scene is a new SCENE starts
                    indexNumber++;
                    lineNumber++;
                    continue;
                }
                string x = "";
                for (int i = 0; i < myText.length(); ++i){
                    if(myText[i] == '.') break;
                    x += myText[i];         // To identify character name differently and store it
                }
                if(x == "CHORUS" || x == "ALL" || x == "BOTH") continue;
                string y = "";
                if(x.length() >= 3) y = x.substr(0, 3);
                if(y == "ACT") continue;
                if(isUpper(x) == true){       
                    mp[x]++;
                }
                lineNumber++;
            }
            scene.push_back(mp);
            cout<<"Enter the character, you want to the list of all other characters which appear in at least one scene with :  ";
            string character;
            cin>>character;
            int count = 0;
            set<string> listCharacters;         // To store all characters required for our operation
            transform(character.begin(), character.end(), character.begin(), ::toupper);
            for(auto i : scene){
                if(i[character] > 0){
                    count++;
                    for(auto j : i){
                        if(j.first == character) continue;
                        listCharacters.insert(j.first);
                    }
                }
            }
            if(count == 0){
                cout<<"No such character!"<<endl;   // If no such character exists
                return;
            }
            cout<<"Following are the characters in atleast one scene with input character : "<<endl;
            for(auto i : listCharacters){
                cout<<i<<endl;          // Printing all characters in atleast one scene with input character
            }
        }
};

class Tasks{ 
    public:
        static void functionalities(string fileName, string fileType, string command){
            int choice;
            Novel myObj1;
            Play myObj2;
            choice = (fileType == "NOVEL")?1:2;         // To direct the control to class Novel or Play 
            switch(choice){                             // Depending on the type of book selected
                case 1 :
                    myObj1.findMaxFrequency(fileName, command);
                    break;
                case 2 :
                    myObj2.findAllCharacters(fileName, command);
                    break;
                default :
                    cout<<"Invalid input"<<endl;        // No valid input
                    break;
            }
        }
};

class Books{     
    private:
        vector<string> allFileName;         // List storing all file names
        map<string, string> mp1, mp2, mp3;      // To store information such as Title, Author and type of book easily accesible by file name
    public:
        Books(string command){ 
            string myText, fileName;
            ifstream MyReadFile("index.txt");
            while(getline (MyReadFile, myText)){
                fileName = myText;    
                allFileName.push_back(fileName);        // Reading all file/books to store their information in above defines lists for easy identification
                ifstream MyFile((command + fileName).c_str());
                while(getline (MyFile, myText)){
                    if(myText.find("Title:") != string::npos){
                        string x = myText.substr(7, myText.length() - 7);
                        mp1[fileName] = x;
                        getline (MyFile, myText);
                        getline (MyFile, myText);
                        x = myText.substr(8, myText.length() - 8);
                        mp2[fileName] = x;
                    } 
                }
                getline (MyReadFile, myText);
                mp3[fileName] = myText;
            } 
        }
        void listAllBooks(){       //  List all books along with their filename, title, and author name
            int index = 0;
            for(auto i : allFileName){
                index++;
                cout<<"File name : "<<i<<endl;      // Printing all details of book
                cout<<"Title : "<<mp1[i]<<endl;
                cout<<"Author : "<<mp2[i]<<endl;
                cout<<"Type : "<<mp3[i]<<endl;
            }
            if(index == 0){
                cout<<"No books present"<<endl;     // No book present
            }
        }
        void displayBook(string bookName, string command){      // Display a book from any of the above two lists
            ifstream MyReadFile((command + bookName).c_str());
            char decide = 'Y';
            string myText;
            while(decide == 'Y'){
                int count = 50;         // Printing only 50 lines (1 page)
                while(count--){
                    getline (MyReadFile, myText);
                    cout<<myText<<endl;
                }
                cout<<"Press Y for next page, N to close book : ";      // To go to next page
                cin>>decide;
            }
        }
        void searchByTitle(string command){         // Search by Title name
            cout<<"Enter the title of the book : ";
            string searchFile;
            getline (std::cin >> std::ws, searchFile);
            int count = 1;
            int index = 0;
            map<int, string> bookKeeper;        // To store a number corresponding to a book for easy operations
            transform(searchFile.begin(), searchFile.end(), searchFile.begin(), ::tolower);
            for(auto i : mp1){
                string fileTitle = i.second;
                transform(fileTitle.begin(), fileTitle.end(), fileTitle.begin(), ::tolower);
                if(fileTitle.find(searchFile) != string::npos){
                    index++;
                    cout<<"Book-"<<count<<endl;             // Printing all details of book
                    cout<<"File name : "<<i.first<<endl;
                    cout<<"Title : "<<mp1[i.first]<<endl;
                    cout<<"Author : "<<mp2[i.first]<<endl;
                    cout<<"Type : "<<mp3[i.first]<<endl;
                    bookKeeper[count] = i.first;
                    count++;
                }
            }
            if(index == 0){
                cout<<"No such book!"<<endl;        // No such book exists
                return;
            }
            cout<<"Do you want to display a book? (Y/N) ";      // To display a book
            char decide;
            cin>>decide;
            int bookNumber;
            while(decide == 'Y'){
                cout<<"Enter book number : ";
                cin>>bookNumber;
                displayBook(bookKeeper[bookNumber], command);
                cout<<endl;
                cout<<"Do you want to display a book? (Y/N) ";
                cin>>decide;
            }
            cout<<"Enter Y if you want to perform analytic tasks? (Y/N) ";      // To perform additional functionalities regarding the book
            cin>>decide;
            while(decide == 'Y'){
                cout<<"Enter book number : ";
                cin>>bookNumber;
                Tasks::functionalities(bookKeeper[bookNumber], mp3[bookKeeper[bookNumber]], command);
                cout<<"Enter Y if you want to perform analytic tasks? (Y/N) ";
                cin>>decide;
            }
        }
        void searchByAuthor(string command){        // Search by Author name
            cout<<"Enter the author of the book : ";
            string searchFile;
            getline (std::cin >> std::ws, searchFile);
            int count = 1;
            int index = 0;
            map<int, string> bookKeeper;        // To store a number corresponding to a book for easy operations
            transform(searchFile.begin(), searchFile.end(), searchFile.begin(), ::tolower);
            for(auto i : mp2){
                string fileTitle = i.second;
                transform(fileTitle.begin(), fileTitle.end(), fileTitle.begin(), ::tolower);
                if(fileTitle.find(searchFile) != string::npos){
                    index++;
                    cout<<"Book-"<<count<<endl;                 // Printing all details of book
                    cout<<"File name : "<<i.first<<endl;
                    cout<<"Title : "<<mp1[i.first]<<endl;
                    cout<<"Author : "<<mp2[i.first]<<endl;
                    cout<<"Type : "<<mp3[i.first]<<endl;
                    bookKeeper[count] = i.first;
                    count++;
                }
            }
            if(index == 0){
                cout<<"No such book!"<<endl;        // No such book exists
                return;
            }
            cout<<"Do you want to display a book? (Y/N) ";      // To display a book
            char decide;
            cin>>decide;
            int bookNumber;
            while(decide == 'Y'){
                cout<<"Enter book number : ";
                cin>>bookNumber;
                displayBook(bookKeeper[bookNumber], command);
                cout<<endl;
                cout<<"Do you want to display a book? (Y/N) ";
                cin>>decide;
            }
            cout<<"Enter Y if you want to perform analytic tasks? (Y/N) ";      // To perform additional functionalities regarding the book
            cin>>decide;
            while(decide == 'Y'){
                cout<<"Enter book number : ";
                cin>>bookNumber;
                Tasks::functionalities(bookKeeper[bookNumber], mp3[bookKeeper[bookNumber]], command);
                cout<<"Enter Y if you want to perform analytic tasks? (Y/N) ";
                cin>>decide;
            }
                
        }
        void searchBooks(string command){       // Search for a book by its title or author name, and show the matching books as a list. 
            cout<<"How do you want to search : "<<endl;
            cout<<"Enter A : To search by its title"<<endl;
            cout<<"Enter B : To search by its author name"<<endl;
            char choice;
            cin>>choice;
            switch(choice){
                case 'A' :
                    searchByTitle(command);
                    break;
                case 'B' :
                    searchByAuthor(command);
                    break;
                default :
                    cout<<"Invalid input"<<endl;        // No valid input given by user
                    break;
            }
        }
};

void file_check(string command){        // Function to identify and store names and type of all files present in a directory
    DIR *dir;
    struct dirent *diread;
    dir = opendir(command.c_str());
    string myText;
    ifstream MyReadFile("index.txt");       // Storing file name and book type in index.txt
    map<string, int> mp1, mp2;
    int count = 0;
    while(getline (MyReadFile, myText)){
        if(count%2 == 1){
            count++;
            continue;
        }
        count++;
        mp1[myText] = 1; 
    }
    vector<pair<string, string> > new_files;
    if(dir != NULL){
        while((diread = readdir(dir)) != NULL){
            if(diread->d_name[0] == '.'){
                continue;
            }
            mp2[diread->d_name] = 1;
            bool flag = false;
            if(mp1[diread->d_name] == 1) flag = true;
            if(flag == false){
                string bookType;
                cout<<"New file detected : "<<diread->d_name<<endl;         // Detecting new files added to the directory 
                cout<<"Input the type of this book : ";
                cin>>bookType;
                mp1[diread->d_name] = 1;
                new_files.push_back({diread->d_name, bookType});
            }
        }
        closedir(dir);
    } else{
        perror("opendir");
    }
    MyReadFile.close();
    ofstream MyWriteFile;
    MyWriteFile.open("index.txt", std::ios_base::app );
    for(auto i : new_files){
        MyWriteFile<<i.first<<endl;         // Writing the information regarding the books in a txt file
        MyWriteFile<<i.second<<endl;
    }
    MyWriteFile.close();
    ofstream MyNewFile;
    MyNewFile.open("indexTemp.txt");
    MyReadFile.open("index.txt");
    while(getline (MyReadFile, myText)){
        if(mp2[myText] == 1){
            MyNewFile<<myText<<endl;
            getline (MyReadFile, myText);
            MyNewFile<<myText<<endl;
        }
        else getline (MyReadFile, myText); 
    }
    remove("index.txt");
    rename("indexTemp.txt", "index.txt");       // Ensuring that if a file is deleted from directory, its data is removed from txt file
    MyNewFile.close();
    MyReadFile.close();
    cout<<endl;
}

int main(int argc, char *argv[]){       // main function
    cout<<"\n\n\t\t\t*******************************************";
    cout<<"\n\t\t\t------------------------------------------";
    cout<<"\n\t\t\t\tLIBRARY MANAGEMENT SYSTEM";
    cout<<"\n\t\t\t------------------------------------------";
    cout<<"\n\t\t\t*******************************************"<<endl<<endl;
    string directory_name;
    cout<<"Enter the directory name you want to open : ";       // Input the directory that one wants to open
    cin>>directory_name;
    string command = "/Users/yagyanshbhatia/Desktop/LMS/" + directory_name + '/';       // Storing path to the directory to access its content
    file_check(command);
    Books LMS(command);
    int choice;
    bool flag = true;
    while(flag){
        cout<<endl<<"What function do you want to perform ? "<<endl;        // What the user want to perform?
        cout<<"Enter 1 : To list all books along with their filename, title, and author name"<<endl;
        cout<<"Enter 2 : To search for a book by its title or author name"<<endl;
        cout<<"Enter 3 : To quit"<<endl;
        cin>>choice;
        switch(choice){
            case 1 :
                LMS.listAllBooks();
                break;
            case 2 :
                LMS.searchBooks(command);
                break;
            case 3 : 
                flag = false;
                break;
            default :
                cout<<"Invalid input"<<endl;        // No valid input
                break;
        }
    }
    return 0;
}