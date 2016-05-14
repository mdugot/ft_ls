# ft_ls
A command similar to the Unix command ls.  
It can be use with some of the options of the original ls :  
-R : Recursively list subdirectories encountered.  
-l : List in long format.  
-r : Reverse order.  
-a : List all entries including those starting with a dot.  
-t : Sort by time modified.  
-u : Use time of last access instead of time of modification.  
-U : Use time of creation instead of time of modification.  
-L : If argument is a symbolic link, list the file or directory the link references rather than the link itself.  
-G : Enable colour output.  
-S : Sort files by size.  
It can be used like the original command :  
> ./ft_ls [-lRartLuUGS] [file ...]  
