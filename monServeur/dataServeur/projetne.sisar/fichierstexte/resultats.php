<!DOCTYPE html>
	
<?php
	
    $nom = isset($_POST['nom']) ? $_POST['nom'] : 'Pas de nom spécifié';	
   
?>
	
<html>
	
    <head>
	
        <meta charset="utf-8"/>
	
    </head>
	
    <body>
	
        <h2>Votre nom</h2>
	
        <p><?php echo $nom; ?></p>
	
	</body>	
</html>
