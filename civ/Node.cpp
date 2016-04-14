#include "Node.h"

Node::Node(int x_, int y_) :
	tile{ nullptr },
	x{ x_ },
	y{ y_ },
	northeast{ nullptr },
	northwest{ nullptr },
	southeast{ nullptr },
	southwest{ nullptr }{
}


Node::~Node(){

}
