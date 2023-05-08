#include <stdio.h>
#include <bfd.h>
#include <malloc.h>
#include <string>
#define DMGL_PARAMS	 (1 << 0)	/* Include function args */
#define DMGL_ANSI	 (1 << 1)
int print_symbol(const char* file_name, uint64_t addr) {
  bfd *abfd;
  asymbol **syms;
  bfd_init();

  abfd = bfd_openr(file_name, NULL);
  if (abfd == NULL) {
    fprintf(stderr, "Failed to open %s\n", file_name);
    return 1;
  }

  if (!bfd_check_format(abfd, bfd_object)) {
    fprintf(stderr, "%s is not an object file\n", file_name);
    return 1;
  }

  if ((bfd_get_file_flags(abfd) & HAS_SYMS) == 0) {
    fprintf(stderr, "%s has no symbols\n", file_name);
    return 1;
  } 
  {
      int storage = bfd_get_symtab_upper_bound(abfd);
      syms = (asymbol **)malloc(storage);
      long number_of_symbols = bfd_canonicalize_symtab(abfd, syms);
      if( number_of_symbols == 0 ) {
        fprintf(stderr, "Failed to canonicalize symbol table\n");
        return 1;
      }

      if (syms == NULL) {
        fprintf(stderr, "syms is NULL \n");
        return 1;
      }


      if (number_of_symbols < 0) {
        fprintf(stderr, "Failed to get symbol table size\n");
        return 1;
      }
      bool print_all = addr == 0;
      for (long i = 0; i < number_of_symbols; i++) {
        if (syms != NULL && syms[i] != NULL && (syms[i]->flags & BSF_FUNCTION)) {
           bfd_vma pc = bfd_asymbol_value(syms[i]);
           if (print_all || pc == addr) {
               asymbol* sym = syms[i];
               const char *filename;
               const char *functionname;
               unsigned int line;

               bfd_find_line(abfd, syms, syms[i], &filename, &line);
               // bfd_find_nearest_line(abfd, bfd_asymbol_section (sym),
			   //  syms, sym->value, &filename,
			   //  &functionname, &line);
               symbol_info ret;
               bfd_symbol_info (syms[i], &ret);
               char *demangled_name = bfd_demangle(abfd, ret.name, DMGL_PARAMS | DMGL_ANSI);

               printf("symbol: %s \t value: %lx \t file: %s \t line: %u \t funcname: %s\n", bfd_asymbol_name(syms[i]), pc, filename, line, demangled_name);
               if (!print_all) {
                   break;
               }
           }
        }
      }
  }
  bfd_close(abfd);
  return 0;
}
int print_symbol(const char* file_name, const char* addr) {
  uint64_t addr_u64 = addr == nullptr ? (uint64_t)0 :std::stoull(addr, nullptr, 16);
  print_symbol(file_name, addr_u64);
  return 0;
}
int main(int argc, char **argv) {
  if (argc < 2) {
      printf("usage ./libbfd_test $file_path [$addr]");
      return -1;
  }
  if (argc == 3) {
      print_symbol(argv[1], argv[2]);
  } else {
      print_symbol(argv[1], nullptr);
  }
  return 0;
}
