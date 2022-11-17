string line;
	string unwantedChars = "``\'\'\'\"\"\"~!@#$%^&*****()--_+=]:;[\\|}{\"\'?/.,><0987654321";
	char p = ' ';
	int cnt = 0;
	

	while (infile >> line)
	{
		getline(infile, line);

		//replacing unwanted characters with a space the unwanted characters
		for (char c : unwantedChars) {
			std::replace(line.begin(), line.end(), c, p);
			//line.erase(std::remove(line.begin(), line.end(), c), line.end());
		}
		stringstream ss(line);
		string word;
		while (ss >> word) {
			cnt ++;
			//making the word lower case
			makeLower(word);
			//cout<<word<<endl;
			Word_Count_Wizard.insert(word);
		}
	}