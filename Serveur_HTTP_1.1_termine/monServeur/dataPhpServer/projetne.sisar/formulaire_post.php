<!DOCTYPE html>
	<html>
		<head>
			<title>Test méthode POST</title>
			<meta charset="utf-8" />
			<meta name="viewport" content="width=device-width, initial-scale=1.0" />
		</head>
		<body> <!-- Corps de la page -->
			<form action="formulaire_post.php" method="POST">	<!-- Début du formulaire -->
				<!-- Liste déroulante -->
				<select name="titre">
					<option>Mlle</option><option selected>Mme</option><option>M.</option>
				</select>
				<!-- Zones de texte -->
				<label for="nom"> Nom : </label><input type="text" name="nom" id="nom" placeholder="Entrez votre nom" /><br/><br/>
				<label for="prenom">Prénom : </label><input type="text" name="prenom" id="prenom" value="Prénom par défaut" /><br/><br/>
				<!-- Bouton radio -->
				<label for="sexe">Sexe : </label>
					<input type="radio" name="sexe" id="sexe" value="H" checked /> Masculin
					<input type="radio" name="sexe" value="F" /> Féminin
				<br/><br/>
				<!-- Slider -->
				<label for="age">Age : 1 </label>
				<input type="range" name="age" id="age" min="1" max="99" step="1" value="18" /> 99
				<br/><br/>
				<!-- Case à cocher -->
				<input type="checkbox" name="bDebutant" checked="checked" /> Je débute en PHP<br/><br/>
				<!-- Bouton -->
				<input type="submit" name="btOK" value="OK">
			</form> <!-- Fin du formulaire -->
			<?php 
				if(isset($_POST['nom']) && $_POST['nom'] != ""){
					echo '<br>Votre nom est : '.$_POST['nom'];
					echo '<br>'
					echo 'Votre prenom est : '.$_POST['prenom'];
					echo '<br>';
					echo 'Et vous avez :'.$_POST['age'].' ans';
				}else{
					echo 'Vous n avez pas de nom';
				}
	
			?>
		</body>
	</html>
