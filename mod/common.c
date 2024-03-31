
void *vtable(void *obj, int offset1, int offset2) {
  return (*(void ***)(obj + offset1))[offset2];
}

void set_vtable(void *obj, int offset1, int offset2, void *func) {
  (*(void ***)(obj + offset1))[offset2] = func;
}
