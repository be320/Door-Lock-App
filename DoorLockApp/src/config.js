import Firebase from 'firebase';
let config = {
  databaseURL: 'https://doorlock-61843.firebaseio.com',
  projectId: 'doorlock-61843',
};
let app = Firebase.initializeApp(config);
export const db = app.database();