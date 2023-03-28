
#ifndef GUI_LISTENER_H
#define GUI_LISTENER_H

class GUI_Listener {
	
	public:
		virtual ~GUI_Listener() {}

		virtual void inicializou() = 0;
		virtual void finalizando() = 0;		
			
		virtual void janelaFechada() = 0;
		
};

#endif
