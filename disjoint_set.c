/* Copyright 2013 miltus31

This file is a part of disjoint set

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include"disjoint_set.h"

#include<stdlib.h>

disjoint_set_forest *create_disjoint_set_forest(size_t size, int (*cmp)(const void *, const void *)){
  disjoint_set_forest *f = (disjoint_set_forest *)malloc(sizeof(disjoint_set_forest));

  f->forest = create_linked_list();
  f->size = size;
  f->cmp = cmp;

  return f;
}

void delete_disjoin_set_forest(disjoint_set_forest *f){
  //  linked_list_free_all(f->forest);
  // have to free node and node->data also
  linked_list *list = f->forest;
  struct linked_list_node *node = list->start;

  while(node!=NULL){
    disjoin_set_node *n = (disjoin_set_node*)node->data;

    list->start = node->next;
    node->next = NULL;

    free(n->data); // disjoint set node also contains some data
    free(node->data);
    free(node);
 
    node = list->start;
  }

  free(f);
}

/* data is stored locally
 */
int make_set(disjoint_set_forest *f, void *data){
  disjoint_set_node *n = (disjoint_set_node *)malloc(sizeof(disjoint_set_node));

  //keeping data locally in the linked list
  //n->data = data;
  n->data = malloc(f->size);
  memcpy(n->data, data, f->size);
  n->parent = n;
  n->rank = 0;

  linked_list_insert(f->forest, n);
}

disjoint_set_forest_node* find(disjoint_set_forest *f, void *data){
  disjoint_set_node *n = (disjoint_set_node *)linked_list_search(f->forest, data, f->cmp);
  
  /* if the node is not found */
  if(n == NULL)
    return NULL;

  return find_r(n);
}

/* Using path compression */
static disjoint_set_forest_node* find_r(disjoint_set_forest_node *n){
  if(n->parent != n)
    n->parent = find_r(n->parent);

  return n->parent;
} 

/* Union by rank */
void set_union(disjoint_set_forest *f, disjoint_set_node *s1, disjoint_set_node *s2){
  disjoint_set_node *root_s1 = find_r(s1);
  dishoint_set_node *root_s2 = find_r(s2);

  //merge
  if(root_s1 != root_s2){
    if(root_s1->rank < root_s2->rank)
      root_s1->parent = root_s2;
    else if(root_s1->rank > root_s2->rank)
      root_s2->parent = root_s1;
    else{
      root_s2->parent = root_s1;
      root_s1->rank++;
    }
  }
}
