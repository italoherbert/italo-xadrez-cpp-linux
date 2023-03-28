#ifndef PECAMOV_H_
#define PECAMOV_H_

class PecaMov {

	private:
		int x1 = -1;
		int y1 = -1;
		int x2 = -1;
		int y2 = -1;
		bool deComp = true;

	public:
		PecaMov( int x1, int y1, int x2, int y2, bool isComp );

		int getX1();
		int getY1();
		int getX2();
		int getY2();
		bool isDeComp();
};

#endif
