#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "rbtree.h"

static inline enum rb_color get_color(struct rbtree_node* node)
{
    if (node == NULL) 
        return RB_BLACK;
    else
        return node->color;
}

static inline void set_color(enum rb_color color, struct rbtree_node* node)
{
    assert(node != NULL);
    node->color = color;
}

// TODO 
