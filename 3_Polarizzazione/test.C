{
    ifstream file1("conc.dat");
    ifstream file2("conc1.dat");

    vector<ifstream*> file = {&file1, &file2};
    //file.push_back(&file1);
    //file.push_back(&file2);
    cout << "sucaaaaa" << endl;

};