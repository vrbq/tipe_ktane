


class Morse
{
  public:

  Morse() {}

    Morse(int led_signal, int led_validation,
             int bouton)
    {
      //Global to local
      led_signal_ = led_signal;
      led_validation_ = led_validation;
      bouton_ = bouton;

      pinMode(led_signal_,OUTPUT);
      pinMode(led_validation_,OUTPUT);
      pinMode(bouton_,INPUT);

      start();
      
    }

  void start()
  {
  

    
  }


  
};

