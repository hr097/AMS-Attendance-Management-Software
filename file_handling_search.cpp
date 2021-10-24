Write-entity(user &u, ofstream &fout)
    fout << u.id << endl
         << u.username << endl
         << u.password << endl
         << ...

Read-entity(user &u, ifstream &fin)
     char ignore_new_line
     fin >> u.id >> ignore_new_line
     fin.getline(u.username, 20);
     fin.getline(u.password, 20);
     ...
     if end of file
         return fail

Insert(user &u)
     ofstream fout("db.dat");
     Write-entity(u, fout);
     fout.close();

Search(char *username) /* for example */
     ifstream fin("db.dat");
     user u;
     vector<user> results;
     while (Read-entity(u))
         if (strcmp(username, u.username) == 0)
             results.push_back(u);
     fin.close();
     return results;

Delete(int level) /* for example */
     ifstream fin("db.dat");
     ofstream fout("db_temp.dat");
     user u;
     while (Read-entity(u))
         if (level != u.level)
             Write-entity(u, fout);
     fin.close();
     fout.close();
     copy "db_temp.dat" to "db.dat"