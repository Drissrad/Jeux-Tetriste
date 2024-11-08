//#include "clavie.cpp" 
#include <iostream>
#include <string.h>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour time()
#include <cstdlib>
#include <random>


using namespace std;

//~class()
//enum
enum class Color {Bleu, Jaun, Rouge, Vert,  nul};
std::string colorToString(Color color) {
    switch (color) {
        case Color::Bleu:
            return "Bleu";
        case Color::Rouge:
            return "Rouge";
        case Color::Vert:
            return "Vert";
        case Color::Jaun:
            return "Jaune";
        default:
            return "Unknown";
    }
}

/*
    Modeles
*/

class Caree{
    public : 
        const string name = "Caree"; 
        Color color;
    Caree(){}
    Caree(Color color){
        this->color = color;
    }

    void show(){
         cout<<"["<< this->name<<"-"<< colorToString(this->color)<<"]";
    }
};

class Circle{
    public: 
        const string name = "Circle"; 
        Color color;

    Circle(){}
    Circle(Color color){
        this->color = color;
    }
    
    void show(){
         cout<<"["<< this->name<<"-"<< colorToString(this->color)<<"]";
    }
};

class Triangle{
    public : 
        const string name = "Triangle"; 
        Color color;
    Triangle(){}
    Triangle(Color color){
        this->color = color;
    }

    void show(){
         cout<<"["<< this->name<<"-"<< colorToString(this->color)<<"]";
    }
};

class Usage{
    public : 
        const string name = "Usage"; 
        Color color;
    Usage(){}
    Usage(Color color){
        this->color = color;
    }

    void show(){
         cout<<"["<< this->name<<"-"<< colorToString(this->color)<<"]";
    }
};



class Form{
    public:
        Caree formCaree;//key 0
        Circle formCircle;// key 1
        Triangle formTriangle;// key 2
        Usage formUsage;// key 3
        int key;
        Form *next;
        Form *prev;
    Form(){}
    Form(Caree ca, Circle c, int i) : formCaree(ca), formCircle(c), key(i),next(nullptr){}//attention pour cette cas , il n'exeste pas dans l'application 
    Form(Caree ca, int i) : formCaree(ca), formCircle(Color::nul), key(i),next(nullptr),prev(nullptr){}
    Form(Circle c, int i) : formCaree(Color::nul), formCircle(c), key(i), next(nullptr), prev(nullptr){}

    void show(){
        if(this->formCaree.color != Color::nul){
            cout<<"["<< formCaree.name<<"-"<< colorToString(formCaree.color)<<"]";
        }else{
            cout<<"["<< formCircle.name<<"-"<< colorToString(formCircle.color)<<"]";
        }
        
    }

    Color getColor(){
        if(key == 0){
            return formCaree.color;
        
        }else if(key == 1){
            return formCircle.color;
        }else if(key == 2){
            return formTriangle.color;
        }
        else if(key == 3){
            return formUsage.color;
        }
        return Color::nul;
    }

     //isEqual
        bool isEqual( Form* f2){
            if(this->key == f2->key) return 1;
            
            Color c1 = this->getColor(), c2 = f2->getColor(); 

            if(c1 == c2)   return 1;

            return 0;    
        }

      
};

class LinkdList{
    private: 
        Form* head;
        Form* tail;
    public: 
        LinkdList(): head(nullptr), tail(nullptr){}

        ~LinkdList(){
            cout<<"Delte Linkdelist"<<endl;

            delete head;
            delete tail;

        }

        //get head
        Form* getHead(){
            return head;
        }

        Form* getTail(){
            return tail;
        }


        //ajouter à la fin de la liste
        void append(Form* f){
            if(tail != nullptr){
                tail->next = f;
                f->prev = tail;
            }
            tail = f;

            if(head == nullptr){
                head = tail;
            }
        }

        //ajouter au début de la liste
        void prepend(Form* f){
            if(head != nullptr){
                head->prev = f;
                f->next = head;
            }
            head = f;
            if(tail == nullptr){
                tail = head;
            }

        }
        
        //affichage
        void show(){
            Form *ptr = head;
            if(head == nullptr){
                cout<<"La liste est vide"<<endl;
                return;
            }
            while(ptr != nullptr){
                if((ptr->formCaree).color != Color::nul){
                    cout<<"["<< ptr->formCaree.name <<"-"<< colorToString(ptr->formCaree.color)<<"]<===>";
                    
                }else if(ptr->formCircle.color != Color::nul)
                {
                    cout<<"["<< ptr->formCircle.name<<"-"<< colorToString(ptr->formCircle.color)<<"]<===>";
                }
                ptr = ptr->next;
            }

            cout<<endl;

        }
        
        //suppression
        bool remove(Form *f){
             // Vérifier si la liste est vide
            if(head == nullptr){
                cout<<"La liste est vide"<<endl;
                return 0;
            }
            //Cas où l'élément à supprimer est en tête de liste
            if(head == f){
                if(head->next != nullptr){
                    head = head->next; 
                    head->prev = nullptr;   
                    delete f;
                    return 1;
                }

                if(head->next == nullptr){
                    head = nullptr;
                    tail = nullptr;
                    delete f;
                    return 1;
                }
                return 0;
            }
            

            if(tail != f){ //Cas où l'élément à supprimer est en centre  de liste
                Form* courent = f;
                courent->prev->next = courent->next;
                courent->next->prev = courent->prev;
                delete f;
                return 1;
            }else{  //Cas où l'élément à supprimer est à la fin de liste
                tail = f->prev;
                f->prev->next = nullptr;

                delete f;
                return 1;
            }

            return 0;
        }

        //Change
        bool change(Form* f1, Form* f2){
            Color color = Color::nul;
            Form f = *f1;
            switch (f1->key){
                case 0:
                    color = f1->formCaree.color;
                        switch (f2->key)
                        {
                            case 0:
                                f1->formCaree.color = f2->formCaree.color;
                                f2->formCaree.color = color;
                                break;
                            case 1:
                                f1->formCaree.color = Color::nul;
                                f1->formCircle.color = f2->formCircle.color;

                                f2->formCircle.color = Color::nul;
                                f2->formCaree.color = f.formCaree.color;
                                break;

                            default:
                                return 0;
                                break;
                        }

                    break;

                case 1:
                    color = f1->formCircle.color;
                        switch (f2->key)
                        {
                            case 0:
                                    f1->formCircle.color = Color::nul;
                                    f1->formCaree.color = f2->formCaree.color;

                                    f2->formCaree.color = Color::nul;
                                    f2->formCircle.color = f.formCircle.color;

                                
                                break;
                            case 1:
                                    f1->formCircle.color = f2->formCircle.color;
                                    f2->formCircle.color = color;
                                break;

                            default:
                                    return 0;
                                break;
                        }
                    
                    break;
            
                default:
                        return 0;
                    break;
            }
            return 1;
        }

       
};



/*
    Controllers
*/

class ControllerForm
{
    public:
        LinkdList list;
        static int indexRemove;
        static int count;
        int time;

    public:
        //create form aléatoire
    Form* Creat(){

        std::random_device rd;
        std::mt19937 gen(rd());
        int randomFormNumber;

        
        
        std::uniform_int_distribution<> dist(0, 3);
        randomFormNumber = dist(gen);
        
        int randomColorNumber = 0 + rand() % (3 - 0 + 1);

        Color color[] = {Color::Bleu, Color::Rouge, Color::Vert, Color::Jaun};
        Form* f1 = new Form(Caree(color[randomColorNumber]), Circle(Color::nul), randomFormNumber);

        switch(randomFormNumber){
            case 0:
                f1->formCaree.color = color[randomColorNumber];
                f1->formCircle.color = Color::nul;
                f1->formTriangle.color = Color::nul;
                f1->formUsage.color = Color::nul;
                break;
            case 1:
                f1->formCircle.color = color[randomColorNumber];
                f1->formCaree.color = Color::nul;
                f1->formTriangle.color = Color::nul;
                f1->formUsage.color = Color::nul;
                break;
            case 2:
                f1->formTriangle.color = color[randomColorNumber];
                f1->formCaree.color = Color::nul;
                f1->formCircle.color = Color::nul;
                f1->formUsage.color = Color::nul;
                break;
            case 3:
                f1->formUsage.color = color[randomColorNumber];
                f1->formTriangle.color = Color::nul;
                f1->formCaree.color = Color::nul;
                f1->formCircle.color = Color::nul;

                break;
            
        }
        return f1;    
    }

    void append(Form* f){
        list.append(f);
        ControllerForm::count ++;
    }

    void prepend(Form* f){
        list.prepend(f);
        ControllerForm::count ++;
    }

    void remove(){
        
        Form* ptr = list.getHead();
        Form* ptrF = list.getTail();
        int i = 0;
        while (true)
        {
            if(ptr == ptrF || ptr->next == nullptr || ptr->next == ptrF || ptr->next->next == nullptr ) break;

            if(ptr->isEqual(ptr->next) && ptr->isEqual(ptr->next->next) &&ptr->next->isEqual(ptr->next->next)){
                    list.remove(ptr); 
                    ControllerForm::indexRemove = i;
                    list.remove(ptr->next);
                   
                    list.remove(ptr->next->next);
                    ControllerForm::count -= 3;
            }

            if(ptr->next->next == ptrF) break;

            ptr = ptr->next;
            i +=1;
        }
        
        
    }

   


};












//[][]

/*
    view
*/

//class ViewForm{
//    public:
//    ControllerForm formController;
//    
//    ViewForm(): formController(){}
//
//    
//    
//    void show(){
//        Form *actualForm;
//        char key;
//        bool winner;
//        formController.append(new Form(Caree(Color::Bleu), Circle(Color::nul), 0));
//        formController.append(new Form(Caree(Color::Jaun), Circle(Color::nul), 0));
//        formController.append(new Form(Caree(Color::nul), Circle(Color::Jaun), 1));
//        
//        
//        do
//        {
//            
//            actualForm = formController.Creat() ;
//
//            
//            
//            
//            
//
//            cout<<endl<<endl <<"=============================================================================="<<endl;
//            cout<<"Pour ajouter au débuit click sur la touche droit "<<endl;
//            cout<<"Pour ajouter à la fin click sur la touche gouche "<<endl;
//            cout<<"Pour quétie click sur Q"<<endl;
//            cout<<"=============================================================================================================="<<endl;
//
//            cout <<"---------------------Voilà la form prochaine : ";
//            actualForm->show();
//             cout <<"--------------------------------------------------------------------------------";
//            cout<<endl;
//
//            formController.list.show();
//            cout<<endl;
//
//            cout<<"Entrez l'option qui vous voullez"<<endl;   
//            key = detecterTouche();
//            
//            if (key == 'q' ||  key == 'Q')
//            {
//                break;
//            }else{
//
//                switch (key)
//                {
//                    case 'G':
//                    case 'g':
//                        formController.prepend(actualForm);
//                        formController.list.show();
//                        formController.remove();
//                        break;
//                    case 'd':
//                    case 'D':
//                        formController.append(actualForm);
//                        formController.list.show();
//                        formController.remove();
//                        break;
//                    default:
//                        break;
//                }
//            } 
//
//            if(ControllerForm::count == 0){
//                system("clear");
//                cout<<endl<<endl<<endl<<endl<<endl<<endl;
//                cout << "\033[47;30m"; // Texte rouge et fond vert
//                    cout << "\033[1m"; 
//                        cout <<"                                Félicitations ! Vous êtes un gagnant !                      " <<endl;
//               
//                break;
//            }else if(ControllerForm::count == 12){
//                system("clear");
//                cout<<endl<<endl<<endl<<endl<<endl<<endl;
//                cout << "\033[47;30m"; // Texte rouge et fond vert
//                    cout << "\033[1m"; 
//                cout <<"-------------------------------->"<< "\033[31;Désolé, vous n'êtes pas un gagnant.\033[0m" << endl;
//                break;
//            }
//        } while (true);
//        cout<<ControllerForm::count<<endl;
//   }
//
//};




