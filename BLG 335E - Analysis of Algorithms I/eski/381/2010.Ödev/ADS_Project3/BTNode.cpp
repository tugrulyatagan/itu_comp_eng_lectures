#include "BTNode.h"

BTNode::BTNode(){
	n=0;
	leaf=false;
	for(int i=0;i<=199;i++){
		keys[i]=NULL;
		c[i]=NULL;
	}
	c[200]=NULL;	
}