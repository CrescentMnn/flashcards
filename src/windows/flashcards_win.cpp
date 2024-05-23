#include <iostream>
#include <windows.h> //sleep f(x)
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <limits>

using namespace std;

//TODO: file handling for saving and reading flashcard sessions

//class for cards

class Cards{
    public:
        int number;
        string question;
        string answer;

};

void save_session(const vector<Cards>& flashcards, ofstream* file) {    

    if (!file || !file->is_open()) {
        cout << "Invalid file stream." << endl;
        return;
    }

    for (const auto& card : flashcards) {
        *file << card.number << "," << card.question << "," << card.answer << endl;
    }

    cout << "Session saved.\n\n" << endl;

    cin.ignore();
}

vector<Cards> readCardsFromFile(const string& filename) {
    vector<Cards> cards;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return cards;
    }

    vector<vector<string>> csvRows; // Vector to store CSV rows

    // Read each line from the CSV file
    for (string line; getline(file, line);) {
        istringstream ss(move(line));
        vector<string> row;
        if (!csvRows.empty()) {
            // We expect each row to be as big as the first row
            row.reserve(csvRows.front().size());
        }
        // std::getline can split on other characters, here we use ','
        for (string value; getline(ss, value, ',');) {
            row.push_back(move(value));
        }
        csvRows.push_back(move(row));
    }

    file.close();

    // Convert csvRows to Cards objects
    for (const auto& row : csvRows) {
        if (row.size() != 3) {
            cout << "Invalid data format in CSV file!" << endl;
            continue;
        }
        Cards card;
        card.number = stoi(row[0]); // Convert string to int for number
        card.question = row[1];
        card.answer = row[2];
        cards.push_back(card);
    }

    return cards;
}

vector<Cards> create_cards(const int size){
    //creates vector (arr) of cards of size 'size'
    vector<Cards> cards_vector(size);

    for(int i=0; i<size; i++){
        Cards card;
        card.number = i+1;
        cout<<"\nQuestion for card "<< i+1 << ": ";
        //cin or getline?
        getline(cin,card.question); //gets input and parses it into the string
        cout<<"\nAnwer for card " << i+1 << ": ";
        //cin >> card.question would stop reading at white space so a question/answer with a space would not be inputted correctly
        getline(cin, card.answer);
        //getline waits until a \n
        cards_vector[i] = card;
    }

    return cards_vector;
}

void clear_screen(){
    for(int m=0; m<50; m++){ cout << "\n" << endl;}
}

void read_cards(const int size, const vector<Cards> &input_vector){

    if(input_vector.empty()){ cout << "\n(-) Vector is empty...." << endl; exit(1);}

    for(int i=0; i<size; i++){
        cout << "\t\tCard number " << i+1 << endl;
        cout << "\nQuestion: " << input_vector[i].question << endl;
        Sleep(1000);
        cout << "\nAnwer: " << input_vector[i].answer << endl;
        Sleep(1000);
    }   
}

void standard_seq(const int size, const vector<Cards> &input_vector){

    if(input_vector.empty()){ cout << "\n(-) Vector is empty...." << endl; exit(1);}

    standard_start:

    cin.ignore();
    clear_screen();

    cout << "\t\t\t+---------------------------------------+\n" << endl;
    cout << "\t\t\t|           Standard Sequence           |\n" << endl;
    cout << "\t\t\t+---------------------------------------+\n" << endl;

    //for choice after end
    int menu_choice = 0;

    cout << "Starting study session...\n\n" << endl;
    cout << "\n\nEach cards question will be printed out, you can answer the question until its correct or escape using the char 'n'\n" << endl;

    Sleep(2 * 1000);

    for(int  i=0; i<size; i++){

        start:
        string gvn_answ;
        cout << "\t\t\tCard number " << i+1 << "\n" << endl;
        cout << "\nQuestion: " << input_vector[i].question << endl;
        cout << "\nAnwer: ";
        while(1){
            getline(cin, gvn_answ);
            if(gvn_answ == "n"){
                cout << "\nExiting...." << endl;
                return;
            }else if(gvn_answ == input_vector[i].answer){
                cout << "\nCorrect answer!!" << endl;
                break;
            }else{ cout << "\nIncorrect answer...\nPlease try again or press 'n' to exit\n\n" << endl; goto start; }
        }
    }

    cout << "\n\nYou've finised the flashcards for this session!!\n" << endl;
    
    while(cout << "\n\n1. Try again\n2. Exit" && !(cin >> menu_choice)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input; please re-enter.\n" << endl;
    }

    if(menu_choice < 1 || menu_choice > 2 ||  cin.fail()){ cout << "\n(-) Input out off bounds...." << endl; exit(0); }

    if(menu_choice == 1){
        goto standard_start;
    }else{
        return;
    }


}

void quiz_sequence(const int size, const vector<Cards> &input_vector){

    if(input_vector.empty()){ cout << "\n(-) Vector is empty...." << endl; exit(1);}

    start:

    cin.ignore();
    clear_screen();

    cout << "\t\t\t+---------------------------------------+\n" << endl;
    cout << "\t\t\t|             Quiz Sequence             |\n" << endl;
    cout << "\t\t\t+---------------------------------------+\n" << endl;

    //same standard sequence but with a grading system
    float grade = 0; //1-10
    //choice after end
    int menu_choice = 0;

    cout << "\nStarting quiz session...\n\nYou will answer the questions as they come, we will not be aware of if they are correct." << endl;
    cout << "\nYour grade will be posted on a scale from 1-10" << endl;

    Sleep(2*1000);

    for(int i=0; i<size; i++){
        string gvn_answ;
        cout << "\t\t\tCard number " << i+1 << "\n" << endl;
        cout << "\nQuestion: " << input_vector[i].question << endl;
        cout << "\nAnwer: ";
        getline(cin, gvn_answ);

        if(gvn_answ == input_vector[i].answer){
            grade += 1;
        }
    }
    
    if(grade == size){
        grade = 10;
    }else{
        grade = (grade/size) * 10;
    }

    cout << "\nYour grade is: " << grade << endl;

    while(cout << "\n1. Try again\n2. Exit" && !(cin >> menu_choice)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input; please re-enter.\n" << endl;
    }

    //err handling
    if(menu_choice < 1 || menu_choice > 2 || cin.fail()){ cout << "\n(-) Input out off bounds...." << endl; exit(0); }

    if(menu_choice == 1){
        goto start;
    }else{
        return;
    }

}

//gets the type of gae the user wants to play
void main_menu(const int size, const vector<Cards> &input_flashcards){
    //prints out options
    int choice = 0;

    cout << "\t\t\t+---------------------------------------+\n" << endl;
    cout << "\t\t\t|               Main Menu               |\n" << endl;
    cout << "\t\t\t+---------------------------------------+\n" << endl;

    while(cout << "\n1. Study session\n2. Quiz session\n3. Exit\n" && !(cin >> choice)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input; please re-enter.\n" << endl;
    }
    //cin.ignore();
    
    //error handling for choice
    if(choice < 1 || choice > 3 || cin.fail()){ cout << "\n(-) Input outside of bounds...\n" << endl; return; }

    if(choice == 1){
        standard_seq(size, input_flashcards);
    }else if(choice == 2){
        quiz_sequence(size, input_flashcards);
    }else{ cout << "\nExiting...\n" << endl; exit(0);}

}

int main(){
    
    //size of arr
    int num_cards;

    //menu choice
    int file_choice = 0;

    //file to use
    string file_name;

    //file obj
    ofstream create_file;
    ifstream open_file;

    //vector of cards
    vector<Cards> new_flashcards;

    cout << "\t\t\t+---------------------------------------+\n" << endl;
    cout << "\t\t\t|           Flashcard Project           |\n" << endl;
    cout << "\t\t\t+---------------------------------------+\n" << endl;
    
    cout << "1. Create a new file\n2. Read a file\n3. Exit\n" << endl;

    cin >> file_choice;

    if(file_choice < 1 ||  file_choice > 3 || cin.fail()){ cout << "(-) Input oustside of bounds..." << endl; exit(1); }

    switch(file_choice){

        case 1: 
        
            cout << "Name of the new file: ";
            cin >> file_name;

            if(cin.fail()){ cout << "error opening file..." << endl; exit(1); }

            file_name+=".txt";

            create_file.open(file_name);

            if(create_file.is_open()){ 
                cout << "File " << file_name << " succesfully!\n" << endl;
            }else { cout << "(-) Error opening file..." << endl; exit(1); }

            cout << "\nPlease input the size of the flashcards: " ;
            cin >> num_cards;

            if(num_cards < 1 || cin.fail()){ cout << "\n(-) Input outside of bounds..." << endl; exit(1);}

            cin.ignore();

            new_flashcards = create_cards(num_cards);   

            cout << new_flashcards.size() << endl;

            save_session(new_flashcards, &create_file);

            create_file.close();

        break;

        case 2: 

            cout << "Enter the name of the existing file: ";
            cin >> file_name;
            if(cin.fail()){ cout << "error opening file..." << endl; exit(1); }

            file_name+=".txt";

            open_file.open(file_name);

            if(open_file.is_open()){
                cout << file_name << " succesfully opened!!\n" << endl;
            }else{
                cout << "(-) Error opening the file..." << endl; exit(1); 
            }

            new_flashcards = readCardsFromFile(file_name);

            num_cards = new_flashcards.size();

            cout << new_flashcards.size() << endl;

            open_file.close();

            cin.ignore();

        break;

        case 3: cout << "Goodbye...\n" << endl; exit(0); break;

        default: cout << "(-) Input oustide of bounds..." << endl; exit(1); break;

    }

    cin.ignore();

    while(1){
        clear_screen();
        main_menu(num_cards, new_flashcards);
    }

    return 0;
}