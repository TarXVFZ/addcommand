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

const int N=5;
Command commands[N];

class Com_class
{
	private:
		string *dir_template = new string[10];
		string *name_template = new string[10];
		
		
		//переменная для хранения размеров блоков
		//или элементов
		string width;

		//размер векторов
		int size;
		
		//тут будет сохранён весь html
//		string html;
	
	public:
		Com_class()
		{
			width = "";
			size = 0;
			//загрузка имён и путей шаблонов
			ifstream file_template("list_template.txt");
			
//			//вектор для директории
//			vector<string> dir_template(10000);
//			//вектор для наименований шаблонов
//			vector<string> name_template(10000);
			
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
				name_template[size] = text_file;
				size++;
			}
			file_template.close();
		}
		
		//обработка входящих команд
		///////////////////////////
		string getting_command(string line)
		{
			line += " ";
			
			//тут будет сохраняться html
			string html="";
			
			//вектор для хранения отдельных команд
			vector<string> cmds(100000);
			int size_vector = 0;
			string str="";
			
			//разделение команд по отдельности
			for (int i=0; i<line.length(); i++)
			{
				if (line[i] != ' ')
					str += line[i];
				else if (i != 0 && line[i-1] != ' ')
				{
					cmds[size_vector] = str;
					size_vector++;
					str = "";
				}
			}
			
//			for (int k=0; k<size_vector; k++)
//				cout << cmds[k] << " ";
//			cout << endl;
			//обработка команд
			for (int i=0; i<size_vector; i++)
			{
				
				if (cmds[i][0] == 'c' && cmds[i][1] == 'r')
				{
					string str_cr="";
					cmds[i] += " ";
					for (int k=3; k<cmds[i].length(); k++)
					{
						if (cmds[i][k] != ' ')
							str_cr += cmds[i][k];
					}
					
					cmds[i] = "cr";
					width = str_cr;
				}
				
				bool container = false;
				for (int j=0; j<N; j++)
				{
					if (commands[j].name == cmds[i])
					{
						//отправка для построения нового контейнера
						html += getting_container(j);
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
				for (int j=0; j<size; j++)
				{
					if (cmds[i] == name_template[j])
					{
//						cout << "this is test ->" << name_template[j] << endl;
						string name_dir = "templates/" + dir_template[j] + "/" + name_template[j] + ".html";
//						cout << "this is test ->" << name_dir << endl;
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
				cout << endl;
			}
			
			return html;
		}
		
		//создание нового контейнера
		//и добавление нового элемента в стек
		/////////////////////////////////////
		string getting_container(int index)
		{
			string dop_html = "";
			if (commands[index].name == "cr")
				dop_html = width + "px\">\n";
				
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
				html += "	<div class=\"clm\">\n" + getting_command(line) + "    </div>\n";
			}
			
			count_commands = count_commands.substr(0, count_commands.length()-4);
			
			return commands[index].html + dop_html + html + "</div>\n";
		}
		
		//Деструктор
		~Com_class()
		{
			delete dir_template;
			delete name_template;
		}
};

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
	
	commands[3].name = "cr";
	commands[3].html = "<div class=\"cr\" style=\"width:";
	
	commands[4].name = "cimg";
	commands[4].html = "<div class=\"cimg\">\n";
	
	
	//новый объект
	Com_class command;
	
	
	//переменная со всем шаблоном
	string html;
	
	for (;;) {
	cout << "Program start!!!!!!!!\n\n> ";
	//считывание первой команды
	getline(cin, html);

	html = command.getting_command(html);
	
	//сохранение шаблона в файле index.html
	ofstream index_html("html/index.html");
	index_html << html;
	index_html.close();
	}
	
	return 0;
}
