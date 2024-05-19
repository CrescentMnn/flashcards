#include <iostream>
#include <unistd.h> //sleep f(x)
#include <string>
#include <vector>
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

vector<Cards> create_cards(int size){
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

void read_cards(int size, const vector<Cards> &input_vector){

    if(input_vector.empty()){ cout << "\n(-) Vector is empty...." << endl; exit(1);}

    for(int i=0; i<size; i++){
        cout << "\t\tCard number " << i+1 << endl;
        cout << "\nQuestion: " << input_vector[i].question << endl;
        sleep(1);
        cout << "\nAnwer: " << input_vector[i].answer << endl;
        sleep(1);
    }   
}

void standard_seq(int size, const vector<Cards> &input_vector){

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

    sleep(1);

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

void quiz_sequence(int size, const vector<Cards> &input_vector){

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

    sleep(2);

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
void main_menu(int size, const vector<Cards> &input_flashcards){
    //prints out options
    int choice = 0;

    cout << "\t\t\t+---------------------------------------+\n" << endl;
    cout << "\t\t\t|               Main Menu               |\n" << endl;
    cout << "\t\t\t+---------------------------------------+\n" << endl;

    //cin.ignore();
    
    while(cout << "\n1. Study session\n2. Quiz session\n3. Exit\n" && !(cin >> choice)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input; please re-enter.\n" << endl;
    }
    
    
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

    cout << "\t\t\t+---------------------------------------+\n" << endl;
    cout << "\t\t\t|           Flashcard Project           |\n" << endl;
    cout << "\t\t\t+---------------------------------------+\n" << endl;
    cout << "\nPlease input the size of the flashcards: " ;
    cin >> num_cards;

    if(num_cards < 1 || cin.fail()){ cout << "\n(-) Input outside of bounds..." << endl; exit(1);}

    cin.ignore();

    vector<Cards> new_flashcards = create_cards(num_cards);

    while(1){
        clear_screen();
        main_menu(num_cards, new_flashcards);
    }

    return 0;
}