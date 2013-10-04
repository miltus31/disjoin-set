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

#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include"linked_list.h"

typedef struct{
  linked_list *forest;
  size_t size; // size of the elements

  //comparison function. required for searching elements
  int (*cmp)(const void *, const void *);

}disjoint_set_forest;

typedef struct{
  disjoint_set_node *parent;
  int rank;
  void *data;
}disjoin_set_node;

disjoint_set_forest *create_disjoint_set_forest(size_t size, int (*cmp)(const void *, const void *));
void delete_disjoin_set_forest(disjoint_set_forest *ds);

// data is stored locally 
int make_set(disjoint_set_forest *f, void *data);

/* Gives the set where the data belongs */
disjoint_set_forest_node* find(disjoint_set_forest *f, void *data);
void set_union(disjoint_set_forest *f, disjoint_set_node *s1, disjoint_set_node *s2);

#endif
