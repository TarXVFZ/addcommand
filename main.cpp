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
		
		
		//���������� ��� �������� �������� ������
		//��� ���������
		string width;
		string height;

		//������ ��������
		int size;
		
		//��� ����� ������� ���� html
//		string html;
	
	public:
		Com_class()
		{
			width = "";
			height = "";
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
				
				if (cmds[i][0] == 'c' && cmds[i][1] == 'i')
				{
					string str_cr="";
					cmds[i] += " ";
					for (int k=5; k<cmds[i].length(); k++)
					{
						if (cmds[i][k] != ' ')
							str_cr += cmds[i][k];
					}
					
					cmds[i] = "cimg";
					height = str_cr;
				}
				
				bool container = false;
				for (int j=0; j<N; j++)
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
			string dop_html = "";
			if (commands[index].name == "cr")
				dop_html = width + "px\">\n";
			if (commands[index].name == "cimg")
				dop_html = height + "px\">\n";
				
			count_commands += "----";
	
			//��� ����������� html
			string html="";
			//���������� ������ �������� ���������
			int count_block;
			cout << "Number of blocks: ";
			cin >> count_block;
			cin.get();
		
			if (count_block !=0)
			{
				string line;
				for (int i=0; i<count_block; i++)
				{
					cout << count_commands << "(" << i+1 << ")> ";
					getline(cin, line);
					html += "	<div class=\"clm\">\n" + getting_command(line) + "    </div>\n";
				}
			} else {
				string line;
				cout << count_commands << "(" << 0 << ")> ";
				getline(cin, line);
				html += "	<div class=\"clm\" style=\"width:100%\">\n" + getting_command(line) + "    </div>\n";
			}
				
			
			count_commands = count_commands.substr(0, count_commands.length()-4);
			
			return commands[index].html + dop_html + html + "</div>\n";
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
	
	commands[3].name = "cr";
	commands[3].html = "<div class=\"cr\" style=\"width:";
	
	commands[4].name = "cimg";
	commands[4].html = "<div class=\"cimg\" style=\"height:";
	
	
	//����� ������
	Com_class command;
	
	
	//���������� �� ���� ��������
	string html;
	string html_start="<!DOCTYPE html>\n<html lang=\"ru\">\n<head>\n<meta charset=\"UTF-8\">\n<title>Acronym</title>\n<link rel=\"stylesheet\" href=\"css/acronym.css\">\n</head>\n";
	string html_stop="\n<script src=\"js/jquery.js\"></script>\n<script src=\"js/acronym.js\"></script>\n</body>\n</html>";
	
	for (;;) {
	cout << "Program start!!!!!!!!\n\n> ";
	//���������� ������ �������
	getline(cin, html);

	html = html_start + command.getting_command(html) + html_stop;
	
	//���������� ������� � ����� index.html
	ofstream index_html("html/index.html");
	index_html << html;
	index_html.close();
	}
	
	return 0;
}
