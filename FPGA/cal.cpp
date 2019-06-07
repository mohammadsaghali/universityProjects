#include <systemc.h>

SC_MODULE (cal){
  sc_in_clk     clock ;      // Clock input of the design
  sc_in <bool>   reset ;      // active high, synchronous Reset input
  sc_in <sc_int<3>> a,b,c,d;
  sc_out <sc_int<10>> result;

  //Local Variables
    void calExp(){
        result.write(0); //Reset
        wait();

        while(true)
        {
            //calcute (a^2 + b^2)^3 - (c^2 + d^2)^2
            result.write(((a.read() * a.read() + b.read() * b.read()) * (a.read() * a.read() + b.read() * b.read()) * (a.read()*a.read() + b.read()*b.read()))
             - ((c.read()*c.read() + d.read()*d.read()) * (c.read()*c.read() + d.read()*d.read())));

            cout<<"@" << sc_time_stamp() <<" :: Incremented Counter "<<result.read()<<endl;

            wait();
        }
      }

    SC_CTOR(cal) {
      SC_CTHREAD(calExp , clock.pos());
      reset_signal_is(reset, true);
    }

      };
