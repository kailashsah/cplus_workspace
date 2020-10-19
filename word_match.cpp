#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional> 

using namespace std;

namespace compare_two_sentence {

	string ltrim(const string &str);
	string rtrim(const string &str);
	vector<string> split(const string &str);

	bool isSimilar(vector<string> sentence_1,
		vector<string> sentence_2,
		vector<vector<string>> similarity_matrix) {

		bool found = true;
		if (sentence_1.size() <= 0 || sentence_2.size() <= 0)
			return false;

		if (sentence_1.size() != sentence_2.size())
			return false;

		for (auto it_sent_1 = 0; it_sent_1 != sentence_1.size(); it_sent_1++)

		{
			// assuming both sentence has equal words ...

			//auto it_find = find(sentence_2.begin(), sentence_2.end(), *it_sent_1);
			if (sentence_2[it_sent_1] == sentence_1[it_sent_1])
			{
				// if found at exact position, good to go for next
				continue;
			}
			else
			{
				// find word in dictionary
				bool found_in_dict = false;
				for (auto it_similar = 0; it_similar != similarity_matrix.size(); it_similar++)
				{
					if (similarity_matrix[it_similar][0] == sentence_1[it_sent_1])
					{
						found_in_dict = true;

						// org word found
						auto it_find = find(similarity_matrix[it_similar].begin(),
							similarity_matrix[it_similar].end(),
							sentence_2[it_sent_1]);

						if (it_find == similarity_matrix[it_similar].end())
							found = false;
					}

				}
				if (!found_in_dict)
					found = false;
			}
		}

		return found;
	}

	void callee_main()
	{
		ofstream fout(getenv("OUTPUT_PATH"));

		string sentence_1_count_temp;
		getline(cin, sentence_1_count_temp);

		int sentence_1_count = stoi(ltrim(rtrim(sentence_1_count_temp)));

		vector<string> sentence_1(sentence_1_count);

		for (int i = 0; i < sentence_1_count; i++) {
			string sentence_1_item;
			getline(cin, sentence_1_item);

			sentence_1[i] = sentence_1_item;
		}

		string sentence_2_count_temp;
		getline(cin, sentence_2_count_temp);

		int sentence_2_count = stoi(ltrim(rtrim(sentence_2_count_temp)));

		vector<string> sentence_2(sentence_2_count);

		for (int i = 0; i < sentence_2_count; i++) {
			string sentence_2_item;
			getline(cin, sentence_2_item);

			sentence_2[i] = sentence_2_item;
		}

		string similarity_matrix_rows_temp;
		getline(cin, similarity_matrix_rows_temp);

		int similarity_matrix_rows = stoi(ltrim(rtrim(similarity_matrix_rows_temp)));

		string similarity_matrix_columns_temp;
		getline(cin, similarity_matrix_columns_temp);

		int similarity_matrix_columns = stoi(ltrim(rtrim(similarity_matrix_columns_temp)));

		vector<vector<string>> similarity_matrix(similarity_matrix_rows);

		for (int i = 0; i < similarity_matrix_rows; i++) {
			similarity_matrix[i].resize(similarity_matrix_columns);

			string similarity_matrix_row_temp_temp;
			getline(cin, similarity_matrix_row_temp_temp);

			vector<string> similarity_matrix_row_temp = split(rtrim(similarity_matrix_row_temp_temp));

			for (int j = 0; j < similarity_matrix_columns; j++) {
				string similarity_matrix_row_item = similarity_matrix_row_temp[j];

				similarity_matrix[i][j] = similarity_matrix_row_item;
			}
		}

		bool result = isSimilar(sentence_1, sentence_2, similarity_matrix);

		fout << result << "\n";

		fout.close();
	}

	
	string ltrim(const string &str) {
		string s(str);

		s.erase(
			s.begin(),
			find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
		);

		return s;
	}

	string rtrim(const string &str) {
		string s(str);

		s.erase(
			find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
			s.end()
		);

		return s;
	}

	vector<string> split(const string &str) {
		vector<string> tokens;

		string::size_type start = 0;
		string::size_type end = 0;

		while ((end = str.find(" ", start)) != string::npos) {
			tokens.push_back(str.substr(start, end - start));

			start = end + 1;
		}

		tokens.push_back(str.substr(start));

		return tokens;
	}
}

/*
int main()
{
	compare_two_sentence:: callee_main();

	return 0;
}
*/

