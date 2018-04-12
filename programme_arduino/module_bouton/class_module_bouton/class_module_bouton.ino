#ifndef ModuleBouton_h
#define ModuleBouton_h









class ModuleBouton
{
  public:

  ModuleBouton() {}

    ModuleBouton(int button_pin, int led_rgb_pin)
    {

      //Local variable to global variable
      button_pin_ = button_pin;
      led_rgb_pin_ = led_rgb_pin;

      pinMode(button_pin_, OUTPUT);
      pinMode(led_rgb_pin_, OUTPUT);

      reset();
      
    }

    void reset()
    {
      //SET le code
    }





  
};




#endif
