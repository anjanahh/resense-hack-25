import React, { useEffect } from "react";
import { Card, CardContent } from "@/components/ui/card";
import { Button } from "@/components/ui/button";
import { UploadCloud, ShoppingCart, Gift, RefreshCcw, Leaf } from "lucide-react";

const civicTips = [
  "🌍 Your city is a reflection of you — keep it clean, keep it kind.",
  "🗳️ Don't just complain. Vote, engage, and be part of the solution.",
  "🚮 Public spaces are shared spaces. Treat them with respect.",
  "📢 Speak up with respect. Report, don’t rant.",
  "🔍 Transparency in government starts with curiosity in citizens."
];

function showCivicTip() {
  const tip = civicTips[Math.floor(Math.random() * civicTips.length)];
  alert(tip);
}

export default function Home() {
  useEffect(() => {
    const timer = setTimeout(() => {
      showCivicTip();
    }, 3000);
    return () => clearTimeout(timer);
  }, []);

  return (
    <div className="min-h-screen bg-blue-50 p-6">
      <h1 className="text-3xl font-bold text-black-800 mb-4"> resense ♻️</h1>
      <p className="text-green-700 mb-6">Use. Reuse. Reinvent. Empowering circular economy through tech.</p>

      <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
        <Card className="hover:shadow-xl">
          <CardContent className="p-4">
            <Gift className="text-green-700 w-8 h-8 mb-2" />
            <h2 className="text-lg font-semibold mb-2">Donate Items</h2>
            <p className="text-sm text-gray-600 mb-3">List unwanted items like electronics, books, or clothes for pickup or exchange.</p>
            <Button variant="outline">Donate Now</Button>
          </CardContent>
        </Card>

        <Card className="hover:shadow-xl">
          <CardContent className="p-4">
            <ShoppingCart className="text-green-700 w-8 h-8 mb-2" />
            <h2 className="text-lg font-semibold mb-2">Buy Upcycled Products</h2>
            <p className="text-sm text-gray-600 mb-3">Support artisans and buy eco-friendly upcycled goods.</p>
            <Button variant="outline">Shop Now</Button>
          </CardContent>
        </Card>

        <Card className="hover:shadow-xl">
          <CardContent className="p-4">
            <UploadCloud className="text-green-700 w-8 h-8 mb-2" />
            <h2 className="text-lg font-semibold mb-2">Classify Waste (AI)</h2>
            <p className="text-sm text-gray-600 mb-3">Upload a photo of waste and get disposal or reuse suggestions instantly.</p>
            <Button variant="outline">Try Classifier</Button>
          </CardContent>
        </Card>

        <Card className="hover:shadow-xl">
          <CardContent className="p-4">
            <RefreshCcw className="text-green-700 w-8 h-8 mb-2" />
            <h2 className="text-lg font-semibold mb-2">Track Pickup</h2>
            <p className="text-sm text-gray-600 mb-3">Schedule and track your e-waste or donation pickup in real time.</p>
            <Button variant="outline">View Status</Button>
          </CardContent>
        </Card>

        <Card className="hover:shadow-xl">
          <CardContent className="p-4">
            <Leaf className="text-green-700 w-8 h-8 mb-2" />
            <h2 className="text-lg font-semibold mb-2">My Impact</h2>
            <p className="text-sm text-gray-600 mb-3">See how much waste you've diverted and CO₂ you've saved.</p>
            <Button variant="outline">View Dashboard</Button>
          </CardContent>
        </Card>
      </div>
    </div>
  );
}
