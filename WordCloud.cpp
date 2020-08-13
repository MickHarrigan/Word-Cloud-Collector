#include "WordCloud.h"

WordCloud::WordCloud(){
    // sets each of the member variables
    m_fileName = "kekeroni.txt";
    m_cloud = new LL<string>();

} // end of default constructor

WordCloud::WordCloud(string filename){
    // sets each of the variables, using the implemented filename
    m_fileName = filename;
    m_cloud = new LL<string>();

} // end of overloaded constructor

WordCloud::~WordCloud(){
    // calls the destructor on the m_cloud LL, empties the string of m_filename
    delete m_cloud;
    m_fileName = "";

} // end of destructor

void WordCloud::LoadFile(){
    // opens the file of m_fileName, and creates a stringstream object
    ifstream File(m_fileName);
    stringstream tempstream;

    if (File.is_open()){
        while (File.peek() != EOF){
            string templine = "";
            // stores each line into a temp
            getline(File, templine);

            // stores the lines as a stringstream
            tempstream << templine;
            string temp;

            // iterates over the stringstream, breaking into temp strings for adding to the m_cloud
            while (getline(tempstream, temp, ' ')){
                // iterates over the string and sets each char to that of the lowercase version
                for (string::iterator it = temp.begin(); it < temp.end(); it++){
                    *it = tolower(*it);

                } // end of for loop

                // removes the punctuation
                RemovePunct(temp);

                // adds the word to the linked list
                m_cloud->Insert(temp);

            } // end of while loop

            // clears the stringstream object for refilling
            tempstream.clear();

        } // end of while loop

    } // end of if statement

    // closes the file
    File.close();

} // end of LoadFile

void WordCloud::RemovePunct(string& word){
    // removes the front punctuation
    if (ispunct(word.at(0))){
        word = word.substr(1, word.size() - 1);

    } // end of if statement

    // removes the back punctuation
    if (ispunct(word.at(word.size() - 1))){
        word = word.substr(0, word.size() - 1);

    } // end of if statement

} // end of RemovePunct

void WordCloud::RemoveCommon(){
    for (int i = 0; i < m_cloud->GetSize(); i++){
        // sets a variable to the words within the m_cloud
        string temp = (*m_cloud)[i].first;

        // checks each word against the excluded list
        for (vector<string>::const_iterator it = EXCLUDE_LIST.cbegin(); it < EXCLUDE_LIST.cend(); it++){
            if (temp == *it){
                // removes the word, and sets the i back one to avoiding skipping over a value
                m_cloud->RemoveAt(temp);
                i--;

            } // end of if statement

        } // end of for loop

    } // end of for loop

} // end of RemoveCommon

void WordCloud::RemoveSingles(){
    vector<string> goodAnswers = {"yes", "y", "no", "n"}; // valid answers to look for
    string choice; // user input of their answer
    bool goodChoiceUser = false; // checks the users input

    // asks the user if they want to remove the singles or not
    do{
        cout << "Would you like to remove all words with a frequency of 1?" << endl;
        getline(cin, choice);

        // makes each char the lowercase version
        for (string::iterator it = choice.begin(); it < choice.end(); it++){
            *it = tolower(*it);

        } // end of for loop

        // checks through the vector of goodAnswers for a viable option
        for (vector<string>::iterator it2 = goodAnswers.begin(); it2 < goodAnswers.end(); it2++){
            if (choice == *it2){
                goodChoiceUser = true;

            } // end of if statement

        } // end of for loop

    // if the input was not in goodAnswers
    } while (!goodChoiceUser);


    // if the singles are to be removed
    int removed = 0;
    if ((choice == "yes") or (choice == "y")){
        // iterates over the list
        for (int i = 0; i < m_cloud->GetSize(); i++){
            // if the quantity is 1, removes it from the list
            if ((*m_cloud)[i].second == 1){
                m_cloud->RemoveAt((*m_cloud)[i].first);
                i--;
                removed++;

            } // end of if statement

        } // end of for loop

        cout << removed << " words removed." << endl;

    } // end of if statement

    else{
        cout << "No words removed" << endl;

    } // end of else statement

} // end of RemoveSingles

void WordCloud::Export(){
    int numWords = 0; // counter for the words that are to be exported
    // takes the name of the file to open
    string filename; // file that the user wants to export to
    cout << "What would you like to call the export file?" << endl;
    cin >> filename;

    // opens the file
    ofstream File(filename);

    for (int i = 0; i < m_cloud->GetSize(); i++){
        // iterates over the list and puts the word and the frequency in the file
        File << (*m_cloud)[i].first << ":" << (*m_cloud)[i].second << endl;
        numWords++;

    } // end of for loop

    cout << numWords << " unique words exported" << endl;

    // closes the file
    File.close();

} // end of Export

void WordCloud::Start(){
    // loads in the file
    LoadFile();

    // removes the required things
    RemoveCommon();
    RemoveSingles();

    m_cloud->Display();

    cout << "END" << endl;

    // calls Export
    Export();

} // end of Start