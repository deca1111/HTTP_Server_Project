#ifndef __HTTPPARSER_H__
#define __HTTPPARSER_H__

void *httpgetRootTree();

typedef struct node {
		int level;
		char *name;
		char *value ;
		int len;
		int explored;
		struct node *link;
		} Lnode ;


		#endif
