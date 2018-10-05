# Autonomous-Parking-System
Purpose

Our purpose is to study and develop an autonomous vehicle that will detect a suitable space (parking position) and will maneuver to be placed inside the parking space.


Implementation

This was achieved by using four ultrasonic sensors (one in front, one in the back of the center of the car and two on the right side of the model car) which take measurements from their environment and push them to a microcontroller, an Arduino in our case. After that, with the software that we developed, the model car "decides" taking in account the data and gives the appropriate commands to the system outputs, ie to the car's engines.

ANALYSIS OF PARKING ALGORITHM

Initially, the model car (mechatron) is positioned at a distance perpendicular to a wall and is approaching it. At a certain distance, the vehicle turns to align with the wall and then follows it (narrow-turn scenario and parking spot search). Then it finds an ideal parking space (when the two side sensors measure the appropriate depth in the same operating cycle), which is greater than twice the length of the particular mechatron (in our case even greater because the model car does not have a large corner angle). So when the ideal parking space is found, the mechatron passes it and starts the parking maneuvers (left and reverse). When the front side sensor reads that the distance from the wall is 2/3 of the width of the vehicle starts to move right-reverse.

More information in doc doc.

# Σύστημα Αυτόματου Παρκαρίσματος
Σκοπός

Σκοπός μας είναι η μελέτη και κατασκευή ενός αυτόνομου οχήματος το οποίο  θα εντοπίζει μια κατάλληλη εσοχή (θέση στάθμευσης) και θα διενεργεί ελιγμούς ώστε να τοποθετηθεί στο εσωτερικό της θέσης (κίνηση παρκινγκ).


Υλοποίηση

Αυτό επιτεύχθηκε με την χρήση τεσσάρων υπέρηχων αισθητηρίων (ένας μπροστά, ένας πίσω στο κέντρο του αμαξιού και δύο στην δεξιά πλευρά του αμαξιδίου) τα οποία παίρνουν μετρήσεις από το περιβάλλον τους και τα οδηγούν σε έναν μικροελεγκτή, στην περίπτωση μας Arduino. Από εκεί και πέρα με το λογισμικό που δημιουργήσαμε, το αμαξίδιο ¨αποφασίζει¨ με βάση τα δεδομένα και δίνει τις κατάλληλες εντολές στις εξόδους του συστήματος, δηλαδή στους κινητήρες του αμαξιού.

ΑΝΑΛΥΣΗ ΑΛΓΟΡΙΘΜΟΥ ΠΑΡΚΑΡΙΣΜΑΤΟΣ 

Αρχικά το μηχατρόνιο τοποθετείται σε κάποια απόσταση κάθετα σε έναν τοίχο και τον πλησιάζει. Σε συγκεκριμένη απόσταση το όχημα στρίβει μέχρι να ευθυγραμμιστεί στον τοίχο και μετά τον ακολουθεί (σενάριο στροφής σε στενό και αναζήτηση θέσης πάρκινγ). Έπειτα βρίσκει έναν ιδανικό χώρο στάθμευσης (όταν μετρήσουν τα δυο πλαϊνά αισθητήρια κατάλληλο βάθος στον ίδιο κύκλο λειτουργίας), ο οποίος είναι μεγαλύτερος από το διπλάσιο μήκος του συγκεκριμένου μηχατρόνιου (στην περίπτωση μας ακόμα μεγαλύτερος γιατί το μηχατρόνιο δεν έχει μεγάλη γωνία στροφής). Οπότε αφού βρεθέι ο ιδανικός χώρος στάθμευσης το μηχατρόνιο τον προσπερνάει  και αρχίζει τους ελιγμούς παρκαρίσματος (αριστερά και όπισθεν).  Όταν το μπροστινό πλαϊνό αισθητήριο διαβάσει ότι η απόσταση από τον τοίχο είναι τα 2/3 του πλάτους του οχήματος αρχίζει κίνηση δεξιά-όπισθεν. 

Περεταίτο πληροφορίες στο αναρτημένο doc.
