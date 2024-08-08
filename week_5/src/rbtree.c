#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  p->nil = (node_t *)calloc(1, sizeof(node_t));
  p->nil->color = RBTREE_BLACK;
  p->nil->left = p->nil->right = p->nil->parent = NULL;
  p->root = NULL;
  return p;
}

void delete_node(node_t *node, node_t *nil) {
  if (node != nil && node != NULL) {
    delete_node(node->left, nil);
    delete_node(node->right, nil);
    free(node);
  }
}

void delete_rbtree(rbtree *t) {
  if (t->root != t->nil) {
    delete_node(t->root, t->nil);
  }
  free(t->nil);
  free(t);
}


void left_rotate(rbtree *t, node_t *current) {
  node_t *new_parent = current->right;
  current->right = new_parent->left;
  if (new_parent->left != t->nil) {
    new_parent->left->parent = current;
  }
  new_parent->parent = current->parent;
  if (current->parent == t->nil) {
    t->root = new_parent; 
  } else if (current == current->parent->left) {
    current->parent->left = new_parent;
  } else {
    current->parent->right = new_parent;
  }
  new_parent->left = current;
  current->parent = new_parent;
}

void right_rotate(rbtree *t, node_t *current) {
  node_t *new_parent = current->left;
  current->left = new_parent->right;
  if (new_parent->right != t->nil) {
    new_parent->right->parent = current;
  }
  new_parent->parent = current->parent;
  if (current->parent == t->nil) {
    t->root = new_parent; 
  } else if (current == current->parent->right) {
    current->parent->right = new_parent;
  } else {
    current->parent->left = new_parent;
  }
  new_parent->right = current;
  current->parent = new_parent;
}

void insert_fixup(rbtree *t, node_t *current) {

  while (current->parent->color == RBTREE_RED) {
    if (current->parent == current->parent->parent->left) {
      node_t *uncle = current->parent->parent->right;  // 삼촌
      if (uncle->color == RBTREE_RED) {  // Case 1
        current->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        current->parent->parent->color = RBTREE_RED;
        current = current->parent->parent;
      } else {
        if (current == current->parent->right) {  // Case 2
          current = current->parent;
          left_rotate(t, current);
        }
        // Case 3
        current->parent->color = RBTREE_BLACK;
        current->parent->parent->color = RBTREE_RED;
        right_rotate(t, current->parent->parent);
      }
    } else {  // 부모가 오른쪽 자식인 경우 (대칭)
      node_t *uncle = current->parent->parent->left;
      if (uncle->color == RBTREE_RED) {
        current->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        current->parent->parent->color = RBTREE_RED;
        current = current->parent->parent;
      } else {
        if (current == current->parent->left) {
          current = current->parent;
          right_rotate(t, current);
        }
        current->parent->color = RBTREE_BLACK;
        current->parent->parent->color = RBTREE_RED;
        left_rotate(t, current->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  new_node->color = RBTREE_RED;
  new_node->key = key;
  new_node->left = new_node->right = t->nil;

  node_t *insert_place = t->nil;
  node_t *current = t->root;

  while (current != t->nil) {
    insert_place = current;
    if (key < current->key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  new_node->parent = insert_place;
  if (insert_place == t->nil) {
    t->root = new_node;
  } else if (key < insert_place->key) {
    insert_place->left = new_node;
  } else {
    insert_place->right = new_node;
  }
  new_node->left = t->nil;
  new_node->right = t->nil;
  new_node->color = RBTREE_RED;

  insert_fixup(t, new_node);
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root; 
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
