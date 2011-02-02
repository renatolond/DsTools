////////////////////////////
// PAlib project template //
////////////////////////////

// Lines starting with two slashes are ignored by the compiler
// Basically you can use them to comment what are you doing
// In fact, this kind of lines are called comments :P

// Include PAlib so that you can use it
#include <PA9.h>
#include "vectorrenderer.h"

int main(){
	// Initialize PAlib
	PA_Init();
        PA_InitText(1, 0);

        Vector2<double> a(1, 1), b(10, 10), c, d, e(3, 4), f, g, h;

        c = b - a;
        d = b * 10;
        f = e.normR();
        g = e.proj(b);
        h = e;
        h.normalize();
        PA_OutputText(1, 1, 1, "%s", a.ToString().c_str());
        PA_OutputText(1, 1, 2, "%s", b.ToString().c_str());
        PA_OutputText(1, 1, 3, "%s", c.ToString().c_str());
        PA_OutputText(1, 1, 4, "%s", d.ToString().c_str());
        PA_OutputText(1, 1, 5, "%s", e.ToString().c_str());
        PA_OutputText(1, 1, 6, "%s", f.ToString().c_str());
        PA_OutputText(1, 1, 7, "%s", g.ToString().c_str());
        PA_OutputText(1, 1, 8, "%s", h.ToString().c_str());
        PA_OutputText(1, 1, 9, "%f1", g.len());
        PA_OutputText(1, 1, 10, "%f1", e.projLen(b));

        VectorRenderer<int> vr;

        Vector2<int> k, l, m, n;
        k = Vector2<int>(2,3);
        l = Vector2<int>(110, 45);
        m = Vector2<int>(110, 112);
        n = Vector2<int>(45, 110);

        std::vector< Vector2<int> > vList;

        vr.SetStyle(2, 0xFF00FF, 0x1);

        vList.push_back(k); vList.push_back(l); vList.push_back(m);

        //vr.DrawLineStrip(vList);
        vr.DrawArc(n, l, m);
	// Put your initialization code here

	// Infinite loop to keep the program running
	while(true){
		// Put your game logic here

		// Wait until the next frame.
		// The DS runs at 60 frames per second.
		PA_WaitForVBL();
	}
}
