// resense-backend/index.js
import express from 'express';
import cors from 'cors';
import dotenv from 'dotenv';

import donationRoutes from './routes/donations.js';
import pickupRoutes from './routes/pickups.js';
import binRoutes from './routes/bins.js';
import aiRoutes from './routes/ai.js';
import impactRoutes from './routes/impact.js';

dotenv.config();

const app = express();
const PORT = process.env.PORT || 5000;

app.use(cors());
app.use(express.json({ limit: '10mb' }));

app.use('/api/donations', donationRoutes);
app.use('/api/pickups', pickupRoutes);
app.use('/api/bins', binRoutes);
app.use('/api/classify', aiRoutes);
app.use('/api/impact', impactRoutes);

app.get('/', (req, res) => {
  res.send('ReSense Backend Running ✅');
});

app.listen(PORT, () => {
  console.log(`🚀 Server running on http://localhost:${PORT}`);
});
