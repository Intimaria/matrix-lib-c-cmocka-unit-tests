#include "../includes/error.h"

const char wrong_input_message[] = "Invalid arguments.\n\nType --help for more information about this program. \n";

int error_help(FILE *fp, error_t e)
{
    switch (e) {
    case E_OK:
        return fprintf(fp, "No error, all OK. See your out file for results.\n");
        break;
    case -E_UNSPECIFIED_ERROR:
        return fprintf(fp, "Unspecified error: %d\n", e);
        break;
    case -E_INPUT_ERROR:
        return fprintf(fp, "Input error: %s\n", wrong_input_message);
        break;
    case -E_NULL:
        return fprintf(fp, "Null value detected error: %d\n", e);
        break;
    case -E_ALLOC_ERROR:
        return fprintf(fp, "Allocation error: %d\n", e);
        break;
    case -E_FORMAT_ERROR:
        return fprintf(fp, "Format error: %d\n", e);
        break;
    case -E_FILE_ERROR:
        return fprintf(fp, "File error: %d\n", e);
        break;
    case -E_READ_ERROR:
        return fprintf(fp, "Read error: %d\n", e);
        break;
    case -E_WRITE_ERROR:
        return fprintf(fp, "Write error: %d\n", e);
        break;
    case -E_SIZE_ERROR:
        return fprintf(fp, "Size error: %d\n", e);
        break;
    case -E_INCOMPATIBLE_MATRIX:
        return fprintf(fp, "Incompatible Matrix error: %d\n", e);
        break;
    case -E_UNIMPLEMENTED_FUNCTION_ERROR:
        return fprintf(fp, "Error: This function hasn't been implemented: %d\n", e);
        break;
    default:
        return fprintf(fp, "Unknown error: %d\n", e);
    }
}


