	#include <iostream>
	#include <cmath>
	
	using namespace std;
	
	class Punkt{
	    double x,y;
	    
	    public:
	        Punkt(); //domyslny
	        Punkt(double x, double y);//konstr. ogolny
	        void setWsp(double x, double y);
	        double getX();
	        double getY();
	        double odlegloscDo( Punkt p);
	};
	
	
	
	int main(){        
	    
		Punkt p;
		Punkt w(7,4);
		cout<<p.getX();
	    
		cout<<endl<<p.odlegloscDo(w);
	    
	    
	}
	
	
	Punkt::Punkt(){x = 0; y = 0;}
	Punkt::Punkt(double px, double py): x{px}, y{py} {}
	
	double Punkt::getX(){ return x; }
	double Punkt::getY(){return y;  }
	void Punkt::setWsp(double x, double y){ 
	    this->x = x;
	    this->y = y;
	}
	double Punkt::odlegloscDo(Punkt p){
	return sqrt( pow( x - p.getX(),2 ) + pow( y - p.getY(),2));
	

}