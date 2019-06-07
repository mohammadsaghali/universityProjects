#include <systemc.h>
#include "cal.cpp"

int sc_main (int argc, char* argv[]) {
  sc_signal<bool>   clock;
  sc_signal<bool>   reset;
  sc_signal<sc_int<3>> a,b,c,d;
  sc_signal<sc_int<10> > result;
  int i = 0;
  cal cal("CAL");
  cal.clock(clock);
  cal.reset(reset);
  cal.result(result);
  cal.a(a);
  cal.b(b);
  cal.c(c);
  cal.d(d);

   sc_start(1, SC_NS);

 //Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("cal");
  // // // Dump the desired signals
    sc_trace(wf, clock, "clock");
    sc_trace(wf, reset, "reset");
    sc_trace(wf, result, "result");
    sc_trace(wf, a, "a");
    sc_trace(wf, b, "b");
    sc_trace(wf, c, "c");
    sc_trace(wf, d, "d");

    reset = 0;       // initial value of reset

   for (i=0;i<5;i++) {
     a = 1;
     b = 1;
     c = 1;
     d = 2 ;

     clock = 0;
     sc_start(1, SC_NS);
     clock = 1;
     sc_start(1, SC_NS);
   }
    reset = 1;    // Assert the reset

     cout << "@ " << sc_time_stamp() <<" :: Asserting reset\n" << endl;
     for (i=0;i<5;i++) {
      clock = 0;
      sc_start(1, SC_NS);
      clock = 1;
      sc_start(1, SC_NS);
    }

    reset = 0;    // De-assert the reset
   cout << "@ " << sc_time_stamp() <<" :: De-Asserting reset\n" << endl;
   for (i=0;i<5;i++) {
     a = 2;
     b = 2;
     c = 1;
     d = 2 ;

     clock = 0;
     sc_start(1, SC_NS);
     clock = 1;
     sc_start(1, SC_NS);
   }

   for (i=0;i<5;i++) {
     a = 1;
     b = 1;
     c = 1;
     d = 1 ;

     clock = 0;
     sc_start(1, SC_NS);
     clock = 1;
     sc_start(1, SC_NS);
   }


}
