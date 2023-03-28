
#ifndef TELA_DRIVER_H
#define TELA_DRIVER_H

class JogoDriver {
	
	public:
		virtual ~JogoDriver() {}

		virtual int getTelaLargura() = 0;
		virtual int getTelaAltura() = 0;
		
		virtual double getFatorCelulaDIM() = 0;
	
		virtual int getInfoPainelAltura() = 0;
};

#endif
