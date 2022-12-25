#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>

//this is an example file, where everything is in one file for "historical" reasons
//please don't write your programs like that, create a normal code structure with headers

//flags to compile:
//g++ -lsfml-window -lsfml-graphics -lsfml-system 


class CGrid: public sf::Drawable{
public:	
	std::vector<bool> field; //remember that you can't use vector<bool> for an MPI version
	std::vector<bool> old_field;
	float step;
	int N_x;
	int N_y;
	mutable sf::RectangleShape dead; //inherited draw is const and complains about trying to modify, mutable negates that!
	mutable sf::RectangleShape alive;
	CGrid();
	CGrid(const int NN_x,const int NN_y,const int s); 
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void click(const int x, const int y);
	void next_generation();
	void reset();
	void save();
	void read(std::ifstream& file);
	void scroll(const char dir);//jumps 5 squares in the direction 
private:
	bool should_i_live(const int i, const int j);
	bool should_i_die(const int i, const int j);	
};
//default constructor
CGrid::CGrid(){
	step=0;
	N_x=0;
	N_y=0;
	dead.setSize(sf::Vector2f(step,step));
	dead.setFillColor(sf::Color::White);
	dead.setOutlineThickness(-1.f);
	dead.setOutlineColor(sf::Color(80,80,80));
	alive.setSize(sf::Vector2f(step,step));
	alive.setFillColor(sf::Color(0,128,0));
}
//constructor with a parameter;
CGrid::CGrid(const int NN_x, const int NN_y, const int s){
	N_x=NN_x;
	N_y=NN_y;
	std::vector<bool> temp(N_x*N_y,false);
	step=s;
	field=temp;
	old_field=temp;
	dead.setSize(sf::Vector2f(step,step));
	dead.setFillColor(sf::Color::White);
	dead.setOutlineThickness(-1.f);
	dead.setOutlineColor(sf::Color(211,211,211));
	alive.setSize(sf::Vector2f(step,step));
	alive.setFillColor(sf::Color(0,128,0));
}

void CGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	for(auto i=0;i<N_y;i++){
		for(auto j=0;j<N_x;j++){
			if (field[i*N_x+j]){
				alive.setPosition(i*step,j*step);
				target.draw(alive);
			}else{
				dead.setPosition(i*step,j*step);
				target.draw(dead);
			}//checking if alive
		}
	}//outer loop
}//draw

void CGrid::save(){
	std::ofstream file("renameMe.txt"); 
	for(auto i=0;i<N_y;i++){
		for(auto j=0;j<N_x;j++){
			file<<field[i*N_x+j]<<" ";
		}
		file<<std::endl;
	}
	file.close();
};


void CGrid::read(std::ifstream& file){//VERY UNSAFE FUNCTION!!! NO CHECKS
	bool temp;
	for(auto i=0;i<N_y;i++){
		for(auto j=0;j<N_x;j++){
			field[i*N_x+j]=temp; //no idea why this doesn't work directly
			file >> temp;
			//file >> field[i*N_x+j];
		}
	}
	old_field=field;
};

void CGrid::reset(){
	std::fill(field.begin(), field.end(), false);
	std::fill(old_field.begin(), old_field.end(), false);
};

void CGrid::click(const int x, const int y){
	int x_coord=(int)x/step;
	int y_coord=(int)y/step;
	field[x_coord*N_x+y_coord]=!field[x_coord*N_x+y_coord];
	old_field[x_coord*N_x+y_coord]=!old_field[x_coord*N_x+y_coord];
};

void CGrid::scroll(const char dir){
	const int jump=5;//in case need to change
	switch (dir){
		case 'd':
			for(auto i=0;i<N_y;i++){
				for(auto j=N_x-jump-1;j<N_x;j++){
					field[i*N_x+j]=false;
				};
			};
			for(auto i=0;i<N_y;i++){
				for(auto j=0;j<N_x-jump-1;j++){
					field[i*N_x+j]=old_field[i*N_x+j+jump];
				};
			};
			break;
		case 'u':
			for(auto i=0;i<N_y;i++){
				for(auto j=0;j<jump;j++){
					field[i*N_x+j]=false;
				};
			};
			for(auto i=0;i<N_y;i++){
				for(auto j=jump;j<N_x;j++){
					field[i*N_x+j]=old_field[i*N_x+j-jump];
				};
			};
			break;
		case 'l':
			for(auto i=0;i<jump;i++){
				for(auto j=0;j<N_x;j++){
					field[i*N_x+j]=false;
				};
			};
			for(auto i=jump;i<N_y;i++){
				for(auto j=0;j<N_x;j++){
					field[i*N_x+j]=old_field[(i-jump)*N_x+j];
				};
			};
			break;
		case 'r':
			for(auto i=N_y-jump-1;i<N_y;i++){
				for(auto j=0;j<N_x;j++){
					field[i*N_x+j]=false;
				};
			};
			for(auto i=0;i<N_y-jump-1;i++){
				for(auto j=0;j<N_x;j++){
					field[i*N_x+j]=old_field[(i+jump)*N_x+j];
				};
			};	
			break;
	}//switch
	old_field=field;
};

bool CGrid::should_i_live(const int i, const int j){
	bool result=false;
	auto counter=0;
	//just manually going through all 8 members, checking if out of bounds
	if ((i>0)&&(i<N_y-1)&&(j>0)&&(j<N_x-1)){
		if (old_field[(i-1)*N_x+j-1]){counter++;}//up left
		if (old_field[(i-1)*N_x+j]){counter++;}//up
		if (old_field[(i-1)*N_x+j+1]){counter++;}//up right
		if (old_field[i*N_x+j-1]){counter++;}//left
		if (old_field[i*N_x+j+1]){counter++;}//right
		if (old_field[(i+1)*N_x+j-1]){counter++;}//down left
		if (old_field[(i+1)*N_x+j]){counter++;}//down
		if (old_field[(i+1)*N_x+j+1]){counter++;}//down right
	} 
	if(counter==3){result=true;}
	return result;
};

bool CGrid::should_i_die(const int i, const int j){
	bool result=false;
	auto counter=0;
	//just manually going through all 8 members, checking if out of bounds
	if ((i>0)&&(i<N_y-1)&&(j>0)&&(j<N_x-1)){
		if (old_field[(i-1)*N_x+j-1]){counter++;}//up left
		if (old_field[(i-1)*N_x+j]){counter++;}//up
		if (old_field[(i-1)*N_x+j+1]){counter++;}//up right
		if (old_field[i*N_x+j-1]){counter++;}//left
		if (old_field[i*N_x+j+1]){counter++;}//right
		if (old_field[(i+1)*N_x+j-1]){counter++;}//down left
		if (old_field[(i+1)*N_x+j]){counter++;}//down
		if (old_field[(i+1)*N_x+j+1]){counter++;}//down right
	} 
	if((counter<2)||(counter>3)){result=true;}
	return result;
};


void CGrid::next_generation(){
	for(auto i=0;i<N_y;i++){
		for(auto j=0;j<N_x;j++){
			if (old_field[i*N_x+j]){
				field[i*N_x+j]=!should_i_die(i,j);
			}else{
				field[i*N_x+j]=should_i_live(i,j);
			};
		};
	};
	old_field=field;	
};

int main(int argc, char *argv[]){	
	const int window_width = 1600;
    const int window_height = 1000;
    CGrid grid(40,64,25);//n_x and n_y "inversed", careful
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Game of Life");
    //window.setVerticalSyncEnabled(true); //for normal video
	//sf::Clock clock;
	if (argc>1){
		std::ifstream config;
		config.open(argv[1]);
		if (!config){
			std::cerr << "Error opening the file. Ignoring." <<std::endl;
		}else{
			grid.read(config);//careful, no checks for dimensions, all hard-coded
		}
	}
	
	bool pause=false, main_game=false, reload=false;
	window.setFramerateLimit(2);
	//need to draw initial picture
	window.clear();
    window.draw(grid);
    window.display();
    window.setKeyRepeatEnabled(false);
    while (window.isOpen()){
		char dir='n';	
		//float t = clock.restart().asSeconds();//time magic
		sf::Event event;
		while (window.pollEvent(event)){
		if (event.type == sf::Event::Closed){window.close();};
		if ((event.type == sf::Event::MouseButtonPressed)&&(event.mouseButton.button == sf::Mouse::Left)){
			grid.click(event.mouseButton.x,event.mouseButton.y);
		};//still processes when running, but they die before showing
		if (event.type == sf::Event::KeyPressed){
				switch (event.key.code){ 
				case sf::Keyboard::Q:
					window.close();
					break;
				case sf::Keyboard::P: //careful, still reads input while paused
					pause=!pause;
					break;
				case sf::Keyboard::Space://careful, still reads input while paused
					pause=!pause;
					break;
				case sf::Keyboard::N: //careful, still reads input while paused
					pause=false;
					main_game=false;
					grid.reset();
					break;	
				case sf::Keyboard::S:
					grid.save();
					break;	
				case sf::Keyboard::Enter:
					main_game=true;
					break;
				case sf::Keyboard::Down:
					dir='d';
					break;
				case sf::Keyboard::R:
					reload=true;
					main_game=false;
					break;
				case sf::Keyboard::Up:
					dir='u';
					break;
				case sf::Keyboard::Left:
					dir='l';
					break;
				case sf::Keyboard::Right:
					dir='r';
					break;
				default: break;
				}
			}//if keypressed    
     //   }//end of event loop
     };
		if(dir!='n'){
			
			grid.scroll(dir);
		};
		if(reload){
			if (argc>1){
				std::ifstream config;
				config.open(argv[1]);
				if (!config){
					std::cerr << "Error opening the file. Ignoring." <<std::endl;
				}else{
					grid.read(config);//careful, no checks for dimensions, all hard-coded
				}
			}
			reload=false;
		}//reload
		if(main_game&&!pause){
			grid.next_generation();
			}
        window.clear();
        window.draw(grid);
        window.display();
    }
    return 0;
} 
