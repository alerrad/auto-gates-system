import { Request, Response, Router } from "express";
import { getTimeStamps, addTimeStamp } from "./handlers/timestamp";


export const router = Router();

router.get("/ping", async (req: Request, res: Response) => {
    return res.json({
        "message": "ping"
    });
});
router.get("/timestamp", getTimeStamps);
router.post("/timestamp", addTimeStamp);