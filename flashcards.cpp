#include <iostream>
#include <windows.h> //sleep f(x)
#include <string>
#include <vector>

using namespace std;

//TODO: file handling for saving and reading flashcard sessions, add a grading feature?

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
        cout<<"Question for card "<< i+1 << ": ";
        //cin or getline?
        getline(cin,card.question); //gets input and parses it into the string
        cout<<"Anwer for card " << i+1 << ": ";
        //cin >> card.question would stop reading at white space so a question/answer with a space would not be inputted correctly
        getline(cin, card.answer);
        //getline waits until a \n
        cards_vector[i] = card;
    }

    return cards_vector;
}

void read_cards(int size, const vector<Cards> &input_vector){
    for(int i=0; i<size; i++){
        cout << "\t\tCard number " << i+1 << endl;
        cout << "Question: " << input_vector[i].question << endl;
        Sleep(1000);
        cout << "Anwer: " << input_vector[i].answer << endl;
        Sleep(1000);
    }   
}

void game_seq(int size, vector<Cards> &input_vector){

    cout << "\t\t\tStarting study session...\t\t\t\n\n" << endl;
    cout << "Each cards question will be printed out, you can answer the question until its correct or escape using the char 'n'\n" << endl;

    Sleep(2 * 1000);

    for(int  i=0; i<size; i++){

        string gvn_answ;
        cout << "\t\t\tCard number " << i+1 << "\n" << endl;
        cout << "Question: " << input_vector[i].question << endl;
        cout << "Anwer: ";
        while(1){
            getline(cin, gvn_answ);
            if(gvn_answ == "n"){
                cout << "Exiting...." << endl;
                exit(1);
            }else if(gvn_answ == input_vector[i].answer){
                cout << "Correct answer!!" << endl;
                break;
            }else{ cout << "Incorrect answer...\nPlease try again or press 'n' to exit" << endl; }
        }
    }

}

int main(){
    
    //size of arr
    int num_cards;

    cout << "\t\t\tFlashcard Project!!\t\t\t" << endl;
    cout << "Please input the size of the flashcards: " ;
    cin >> num_cards;
    cin.ignore();

    vector<Cards> new_flashcards = create_cards(num_cards);

    read_cards(num_cards, new_flashcards);
    game_seq(num_cards, new_flashcards);

    return 0;
}