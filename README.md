![logo](logo.jpg)

# Moutarde

`Moutarde` is a data structured language like `Json` or `XML`, see `teste.moutarde`.
The particularity is that it relies on pair of parenthesis to structure data, and all the data must have at least one name in commun as you can see in `teste.moutarde`.

As `XSLT` is to `XML`, `instruct` files are where the instructions for the html output are. The queries are also given inside pair of parenthesis, see `teste.instruct`

For now, these instructions are supported:

## Value

`v` is used as the keyword for a `value`

The value query is defined via its `path` inside the `moutarde` file.

For example, the following query will search for the first boo ktitle it finds.

teste1.instruct:

```
<!DOCTYPE html>
<html lang="en">
<head>
        <title> Teste </title>
        <link rel = "stylesheet" href = "style.css">
        <meta charset="utf-8"/>
</head>
(<body>

        (f:destination:
        
         <ul>
             <li> (v:bookstore/book/title:) </li>
        </ul>
         
         )

</body>
)
```

teste.cpp:

```
#include "moutarde.h"

int main() {
 
  std::string instruct_file = "teste1.instruct";
  std::string moutarde_file = "teste.moutarde";
  std::string html_file = "teste.html";
  unsigned int end_head = 6;

  moutardify(moutarde_file, instruct_file, html_file, end_head);

  return 0;
};
```

## For loop

`f` is used as the keyword for a `for loop`

Where the `for loop` loops is defined via its `path` inside the `moutarde` file.
Of course, you can `for loop` inside another `for loop`, and so on...

For example, the folowing query will search for all the books title inside the bookstore.

teste1.instruct:

```
<!DOCTYPE html>
<html lang="en">
<head>
        <title> Teste </title>
        <link rel = "stylesheet" href = "style.css">
        <meta charset="utf-8"/>
</head>
(<body>

        (f:destination:
        
         <ul>
          (f:bookstore/book:
             <li> (v:title:) </li>
          )
        </ul>
         
         )

</body>
)
```

teste.cpp:

```
#include "moutarde.h"

int main() {
 
  std::string instruct_file = "teste1.instruct";
  std::string moutarde_file = "teste.moutarde";
  std::string html_file = "teste.html";
  unsigned int end_head = 6;

  moutardify(moutarde_file, instruct_file, html_file, end_head);

  return 0;
};
```

## Where / If - Conditions

`w` is used as the keyword for a `condition`

The `evaluation variable` of the condition is defined via its `path` inside the `moutarde` file.

The conditions is defined after the `path` and the `:` character, as you see in the following example.

The supported conditions are: 

- `=` is equal to at least one inside `[x1,x2,x3...]` ?
- `>` is greater than at least one in `[x1,x2,x3...]` ? - in future version
- `<` is lower than at least one in `[x1,x2,x3...]` ? + in future version
- `!` is not equal to at least one in `[x1,x2,x3...]` ?

Of course, you can interwine conditions to make a `AND` condition.

For example, the following query will list all the books that were published in the year 2003.

teste1.instruct:

```
<!DOCTYPE html>
<html lang="en">
<head>
        <title> Teste </title>
        <link rel = "stylesheet" href = "style.css">
        <meta charset="utf-8"/>
</head>
(<body>

        (f:destination:
        
         <ul>
          (f:bookstore/book:
            (w:year:=[2003]
               <li> (v:title:) </li>
             )
          )
        </ul>
         
         )

</body>
)
```

teste.cpp:

```
#include "moutarde.h"

int main() {
 
  std::string instruct_file = "teste1.instruct";
  std::string moutarde_file = "teste.moutarde";
  std::string html_file = "teste.html";
  unsigned int end_head = 6;

  moutardify(moutarde_file, instruct_file, html_file, end_head);

  return 0;
};
```

## Sort 

Sorting result returned in a `for loop`, is defined putting the `-` character or the `+` character after the variable `path` of the `for loop` to respectively perform a descending and ascending sort. The variable from which the sort is based is defined after the `-` or `+` and `:` character, see example (must end with `:`)
You can interwine `for loop` with `sorting` enabled.

For example, the following query will search for all the prices of the books in the bookstore according to the country and sort their price decreasingly. It will sort the books in increasing order.

teste1.instruct:

```
<!DOCTYPE html>
<html lang="en">
<head>
        <title> Teste </title>
        <link rel = "stylesheet" href = "style.css">
        <meta charset="utf-8"/>
</head>
(<body>
         (f:destination:
           (f:bookstore/book:+:title:
               <ul>
                 (f:price/country:-:price:
                     <li>here 1: (v:price:)</li>
                 )
                
               </ul>
           )
        )
</body>
)
```

teste.cpp:

```
#include "moutarde.h"

int main() {
 
  std::string instruct_file = "teste1.instruct";
  std::string moutarde_file = "teste.moutarde";
  std::string html_file = "teste.html";
  unsigned int end_head = 6;

  moutardify(moutarde_file, instruct_file, html_file, end_head);

  return 0;
};
```

## Path

As you see each path must be closed by the `:` character
