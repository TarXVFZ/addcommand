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

class Com_class
{
	private:
//		//������ ��� ����������
//		vector<string> dir_template();
//		//������ ��� ������������ ��������
//		vector<string> name_template();
	
		string *dir_template = new string[10];
		string *name_template = new string[10];

		//������ ��������
		int size;
		
		//��� ����� ������� ���� html
//		string html;
	
	public:
		Com_class()
		{
			size = 0;
			//�������� ��� � ����� ��������
			ifstream file_template("list_template.txt");
			
//			//������ ��� ����������
//			vector<string> dir_template(10000);
//			//������ ��� ������������ ��������
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
		
		//��������� �������� ������
		///////////////////////////
		string getting_command(string line)
		{
			line += " ";
			
			//��� ����� ����������� html
			string html="";
			
			//������ ��� �������� ��������� ������
			vector<string> cmds(100000);
			int size_vector = 0;
			string str="";
			
			//���������� ������ �� �����������
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
			
			//��������� ������
			for (int i=0; i<size_vector; i++)
			{
				bool container = false;
				for (int j=0; j<3; j++)
				{
					if (commands[j].name == cmds[i])
					{
						//�������� ��� ���������� ������ ����������
						html += getting_container(j);
						container = true;
						break;
					}
				}
				
				//�������� �� ��, �������� ������� � ���� �������� �����������
				if (container)
					continue;
				
				//���� ������� �� ������������,
				//�� ����� �������� ������� ��������
				//� ������������ � ������
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
		
		//�������� ������ ����������
		//� ���������� ������ �������� � ����
		/////////////////////////////////////
		string getting_container(int index)
		{
			count_commands += "----";
	
			//��� ����������� html
			string html="";
			//���������� ������ �������� ���������
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
			
			return commands[index].html + html + "</div>\n";
		}
		
		//����������
		~Com_class()
		{
			delete dir_template;
			delete name_template;
		}
};

/////
//�������� ���������
//////////////////////////////////////////////
int main()
{
	//�������� �����������
	commands[0].name = "cc";
	commands[0].html = "<div class=\"cc\">\n";
	
	commands[1].name = "cp";
	commands[1].html = "<div class=\"cp\">\n";
	
	commands[2].name = "cw";
	commands[2].html = "<div class=\"cw\">\n";
	
	
	//����� ������
	Com_class command;
	
	
	//���������� �� ���� ��������
	string html;
	
	for (;;) {
	cout << "Program start!!!!!!!!\n\n> ";
	//���������� ������ �������
	getline(cin, html);

	html = command.getting_command(html);
	
	//���������� ������� � ����� index.html
	ofstream index_html("html/index.html");
	index_html << html;
	index_html.close();
	}
	
	return 0;
}
