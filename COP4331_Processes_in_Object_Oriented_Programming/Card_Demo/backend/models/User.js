const mongoose = require('mongoose');

const userSchema = new mongoose.Schema({
  Username: { type: String, required: true, unique: true },
  Password: { type: String, required: true },
  FirstName: { type: String, required: true },
  LastName: { type: String, required: true }
});

module.exports = mongoose.model('User', userSchema);
