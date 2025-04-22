#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* help = "usage: h - help, s - see all miNettes, a - add miNette, d - delete miNette\n";

struct user_note {
  int id; // 4 bytes
  char *text; // 8 bytes
};

struct VectorBombordino {
  size_t size; // Element count (8 bytes)
  size_t capacity;// Texy axper jan (8 bytes)
  struct user_note *data; // El ur aranc himnakana data-i axper jan (12 bytes)
                          // obshi 28 byte
};

typedef struct VectorBombordino VectorBombordino; // so we don't put struct everytime before VectorBombordino type
typedef struct user_note user_note; // so we don't put struct everytime before user_note type


size_t size(VectorBombordino *); // return number of elements in a given VectorBombordino pointer

void init_un(user_note *un){ // initialize user note
  un->text = strdup("No notes, add some to see some...");
  un->id = 0;
}


void add_text_to_note(user_note *note, char *text, int *id) {
   int text_len = strlen(text);

   note->text = calloc(sizeof(char), text_len); // allocate 8 * size of text
   strcpy(note->text, text); // copy user supplied text to allocated space
   note->id = *id;
}
void list_notes(VectorBombordino *vectornash, user_note *un){
  size_t element_count = size(vectornash); // get current number of elements in the vectornash pointer
  if(element_count == 0) {
    printf("\n%s\n", un->text);
  }
  for (size_t i = 0; i < element_count; i++) { // iterate through elements
    printf("ID: %d:  %s\n", vectornash->data[i].id,vectornash->data[i].text); // print all the text in the elements
  }
}

void delete_note(VectorBombordino *vectornash, int *to_delete){
  size_t index = -1; // invalid number

  for(size_t i = 0; i < vectornash->size; i++){
    if(vectornash->data[i].id == *to_delete){
      index = i;
      break;
    }
  }
  if(index == (size_t)-1){
        printf("Note with ID %d not found.\n", *to_delete);
        return;
      }
  free(vectornash->data[index].text);

  for(size_t i = index; i < vectornash->size -1; i++){
    vectornash->data[i] = vectornash->data[i + 1];
  }
  vectornash->size--;
}


void init(VectorBombordino *vectornash) { // initialize a vector
  if (vectornash == NULL)  {
    printf("lav ches ay txa");
    return;
  }

  vectornash->capacity = 0;
  vectornash->size = 0;
  vectornash->data = NULL;
}


// Helper function
void empty_vector_handle(VectorBombordino *vectornash) {
  vectornash->data = calloc(1, sizeof(user_note));
  vectornash->capacity = 1;
  // Size is zero bruh
  // don't need this anymore
}

void resize(VectorBombordino *vectornash) {
  vectornash->capacity = vectornash->capacity == 0 ? 1 : vectornash->capacity * 2; // if the capacity of the vwctor is 0
                                                                                   // make it 1
                                                                                   // else multiply the capacity by 2

  user_note *new_data = realloc(vectornash->data, vectornash->capacity * sizeof(user_note)); // reallocate space for data, with the size of current capacity * 12 (user_note type)
  if(new_data == NULL){
    printf("Hop, chelav aper...");
    return;
  }
  vectornash->data = new_data; // put the data into the newly allocated space
}

void push_back(VectorBombordino *vectornash, user_note *note) { // dynamic memory allocation
  if (vectornash->size >= vectornash->capacity) {
    resize(vectornash);
  }
  vectornash->data[vectornash->size] = *note; // go get the note from the provided pointer
                                              // put it in the corresponding index in our array
  ++vectornash->size; // increment the size by one
}

size_t size(VectorBombordino *vectornash) { // return the size of size?
  return vectornash->size;
}

void destructor(VectorBombordino *vectornash) {
  for (size_t i = 0; i < size(vectornash); i++) { // iterate over elements in our array
    free(vectornash->data[i].text); // free allocated memory for text
  }
}

int main() {
  VectorBombordino vector_object;

  user_note un_object;

  init(&vector_object); // initialize vector
  init_un(&un_object); // initialize user note
  int id = 0;
  const int ARRAY_SIZE = 256;
  int to_delete;
  char note_buf[ARRAY_SIZE];
  for (size_t i = 0; i < ARRAY_SIZE; ++i) {
    note_buf[i] = 0; // clean the buffer before giving it to the user
  }
  printf("***Welcome to miNettes***\n");
  puts(help);
  while(1) {
    char method;
    printf("Input: ");
    fflush(stdout);
    scanf("  %c", &method);
    switch (method) {
    case 'q':
      printf("Cleaning up...\n");
      destructor(&vector_object);
      printf("bye!\n");
      return 0;
      break;

    case 'd':
      printf("Enter miNette id to delete: ");
      scanf(" %d: ", &to_delete);
      delete_note(&vector_object, &to_delete);
      break;
    case 'h':
      puts(help);
      break;
      case 's':
      list_notes(&vector_object,&un_object);
      break;
    case 'a':
      id++;
      puts("*Start typing your miNette*");
      user_note note;
      scanf(" %[^\n]s", note_buf);
      add_text_to_note(&note, note_buf, &id); // allocates memory for the note
      push_back(&vector_object,&note); // pushes the note to our array
      puts("*miNette Saved*");

      // Clear draft area
      for (size_t i = 0; i < strlen(note.text); ++i) {
        note_buf[i] = 0;
      }

      break;
    }
  }

  return 0;
  }


/* TODO:
 *
 * 1) asigning id's to notes.
 * 2) deleting notes based on id.
 * 3) capturing CTR+C and calling destructor before ending application process
 */
