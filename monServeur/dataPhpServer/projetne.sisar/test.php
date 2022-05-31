

<?php
echo "<html>";
echo "<head>";
echo "<title> Comment utiliser un code PHP dans une page HTML </title>";
echo "</head>";
echo "<body>";
setlocale (LC_TIME, 'fr_FR.utf8','fra');
echo "Bonjour, aujourd'hui c'est le ";
echo (strftime("%A %d %B %Y")) ;
echo "</body>";// autre code php ici 
echo "</ html>" 
?>
