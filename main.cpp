#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Command {
	string name;
	string html;
};

int size_file_vector = 0;

string count_commands = "";

const int N=3;
Command commands[N];

string getting_command(string line, vector<string> dir_template, vector<string> name_template);
string getting_container(int index, vector<string> dir_template, vector<string> name_template);

/////
//ОСНОВНАЯ ПРОГРАММА
//////////////////////////////////////////////
int main()
{
	//описание контейнеров
	commands[0].name = "cc";
	commands[0].html = "<div class=\"cc\">\n";
	
	commands[1].name = "cp";
	commands[1].html = "<div class=\"cp\">\n";
	
	commands[2].name = "cw";
	commands[2].html = "<div class=\"cw\">\n";
	
	//загрузка имён и путей шаблонов
	ifstream file_template("list_template.txt");
	
	//вектор для директории
	vector<string> dir_template(10000);
	//вектор для наименований шаблонов
	vector<string> name_template(10000);
	
	int size = 0;
	string text_file;
	while(getline(file_template, text_file))
	{
		string str="";
		for (int i=0; i<text_file.length(); i++)
		{
			if (text_file[i] != '_')
				str += text_file[i];
			else break;
		}
			
		dir_template[size] = str;
		cout << text_file << endl;
		name_template[size] = text_file;
		size++;
	}
	file_template.close();
	size_file_vector = size;
	
	
	
	//переменная со всем шаблоном
	string html;
	
	cout << "> ";
	//считывание первой команды
	getline(cin, html);
//	cout << container_command(html) << endl;

	html = getting_command(html, dir_template, name_template);
	
	//сохранение шаблона в файле index.html
	ofstream index_html("html/index.html");
	index_html << html;
	index_html.close();
	
	return 0;
}

string getting_container(int index, vector<string> dir_template, vector<string> name_template)
{
	count_commands += "----";
	
	//тут сохраняется html
	string html="";
	//количество блоков дочерних элементов
	int count_block;
	cout << "Number of blocks: ";
	cin >> count_block;
	cin.get();

	string line;
	for (int i=0; i<count_block; i++)
	{
		cout << count_commands << "(" << i+1 << ")> ";
		getline(cin, line);
		html += "	<div class=\"clm\">\n" + getting_command(line, dir_template, name_template) + "    </div>\n";
	}
	
	count_commands = count_commands.substr(0, count_commands.length()-4);
	
	return commands[index].html + html + "</div>\n";
}

string getting_command(string line, vector<string> dir_template, vector<string> name_template)
{
	line += " ";
	
	//тут будет сохраняться html
	string html="";
	
	//вектор для хранения отдельных команд
	vector<string> cmds(1);
	int size = 0;
	string str="";
	
	//разделение команд по отдельности
	for (int i=0; i<line.length(); i++)
	{
		if (line[i] != ' ')
			str += line[i];
		else if (i != 0 && line[i-1] != ' ')
		{
			cmds[size] = str;
			size++;
			str = "";
		}
	}
	
	//обработка команд
	for (int i=0; i<size; i++)
	{
		bool container = false;
		for (int j=0; j<3; j++)
		{
			if (commands[j].name == cmds[i])
			{
				//отправка для построения нового контейнера
				html += getting_container(j, dir_template, name_template);
				container = true;
				break;
			}
		}
		
		//проверка на то, является команда в этой итерации контейнером
		if (container)
			continue;
		
		//если команда не контейнерная,
		//то будут искаться блочные элементы
		//и записываться в шаблон
		for (int j=0; j<size_file_vector; j++)
		{
			if (cmds[i] == name_template[j])
			{
				string name_dir = dir_template[j] + "/" + name_template[j] + ".html";
				const char* name_file_char = name_dir.c_str();
				ifstream file_html(name_file_char);
				
				string line_html;
				while(getline(file_html, line_html))
				{
					html += line_html;
				}
				file_html.close();
				
				break;
			}
		}
	}
	
	return html;
}
