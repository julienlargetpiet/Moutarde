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

## For loop

`f` is used as the keyword for a `for loop`

Where the `for loop` loops is defined via its `path` inside the `moutarde` file.

For example, the folowing query will search for all the books title inside the bookstore.

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

## Where / If - Conditions

`w` is used as the keyword for a `condition`

The `evaluation variable` of the condition is defined via its `path` inside the `moutarde` file.

The conditions is defined after the `path` and the `:` character, as you see in the following example.

The supported conditions are: 

- `=` is equal ?
- `>` is greater ?
- `<` is lower ?
- `!` is not equal ?
- `E` belongs to [min,max] ? (working on it)

For example, the following query will list all the books that were published in the year 2003.

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

## Sort 

Working on it

## Path

As you see each path must be closed by the `:` character
